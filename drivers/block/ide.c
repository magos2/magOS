/* Copyright 2016 @AR
 *
 * Basic PIO ATA driver implementation based on ATA 6 standard.(www.t13.org)
 * see: ATA/ATAPI Command Set 3 (by T13.org) [ATA/ATAPI 8]
 *
 * http://forum.osdev.org/viewtopic.php?f=1&p=167798#p167798
 * http://wiki.osdev.org/PCI_IDE_Controller
 * http://wiki.osdev.org/PIO_Mode
 *
 * only sector number start from 1, other(h,c,lba) start from 0.
 * LBA and CHS equivalence : with 16 heads per cylinder
	LBA value	CHS tuple
	0			0, 0, 1
	1			0, 0, 2
	2			0, 0, 3
	62		   0, 0, 63
	63		   0, 1, 1
	945		  0, 15, 1
	1007		 0, 15, 63
	1008		 1, 0, 1
 * ATA controller:
   - Drive/Head register.  addr: 0x1F6. format: [7:1 6:LBA 5:1 4:DRV 3-0:HEAD]
     DRV: this bit is used to select the drive. Master is 0, Slave 1.
     101x 0000
  * IDE Naming, major/minor numbers:
    primary  ; ide0; port 0x1f0; major=3;  hda minor=0;  hdb minor=1
    secondary; ide1; port 0x170; major=3;  hdc minor=2; hdd minor=3
          
    hda1  major=3; minor=16
    hda2  major=3; minor=17
    hda15 major=3; minor=31
    hdb1  major=3; minor=32
    hdcX  major=3; minor=64+X
    
    this driver can manage up to 16 drives.
    a disk can be partitioned into 16 partitions max.
    
    see http://www.ibm.com/support/knowledgecenter/STUVMB/com.ibm.storage.ssic.help.doc/f2c_linuxdevnaming_2hsag8.html
    
  * The standard port, and irq values are these:
	ide0=0x1f0,0x3f6,14
	ide1=0x170,0x376,15
	
  * device identification:
   - major : (device >> 8), determine de drive class(hd, cdrom, ...)
   - minor : (device & 0xff), identify the device in a class 
   - dev = (major<<8 | minor)
 */
#define KERNEL_DEBUG 0
#include <ide.h>
#include <ext2.h>
#include <io.h>
#include <errno.h>
#include <kernel.h>
#include <mm.h>
#include <libc.h>
#include <string.h>
#include <types.h>
#include <config.h>
#include <wait.h>

dev_t root_dev;
struct disk* root_hd;
device_t * ide_dev[IDE_MAXDEV] = {NULL,}; /*table index is the minor*/

controller_t controllers[2] = {{.id=PRIMARY_CTRL,
                                .base=PRIMARY_CTRL_BASE,
                                .irq=14,
                                .locker=NULL,
                                .mutex=0}, 
                               {.id=SECONDARY_CTRL,
                                .base=SECONDARY_CTRL_BASE,
                                .irq=15,
                                .locker=NULL, .mutex=0}};


#define BSY(status) (status & STATUS_BSY)
#define DRQ(status) (status & STATUS_DRQ)
#define REG(ctrl,reg)       (ctrl->base+reg)

#define read_status(ctrl)           inb(ctrl->base+REG_STATUS)
#define read_alt_status(ctrl) inb(ctrl->base+REG_ALT_STATUS)

#define ata_inb(channel,reg) inb(channel->base + reg) 
#define ata_outb(channel,value,reg) outb(value, channel->base+reg);

unsigned char register_ide_device (device_t *device)
{
  if (ide_dev[device->minor]) 
    return -EBUSY;
  ide_dev[device->minor] = device;
  return device->minor;
}

void unregister_ide_device (device_t *device)
{
  ide_dev[device->minor] = NULL;
  kfree(device);
}

int inline is_busy (controller_t *ctrl)
{
  return (inb(ctrl->base+REG_STATUS) & STATUS_BSY);
}

char* ata_error(unsigned char err)
{
  if (err & ERR_BBK)       return "Bad Block";
  else if (err & ERR_UNC)  return "Uncorrectable data error";
  else if (err & ERR_MC)   return "Media Changed";
  else if (err & ERR_IDNF) return "ID mark Not Found";
  else if (err & ERR_MCR)  return "Media Change Requested";
  else if (err & ERR_ABRT) return "command aborted";
  else if (err & ERR_TK0NF)return "Track 0 Not Found";
  else if (err & ERR_AMNF) return "Address Mark Not Found";
  return "No error, strange!"; 
}


/*Delay 400ns after each command sent to controller.
 *a common way to simulate the 400ns delay is to read 
 *the aternate status register 4 times.*/
void delay_400ns(controller_t* ctrl)
{
  read_alt_status(ctrl);  read_alt_status(ctrl);
  read_alt_status(ctrl);  read_alt_status(ctrl);
}

int ata_poll(controller_t *ctrl)
{
  unsigned char status;
  
  delay_400ns(ctrl);
  
  /* polling status until BSY bit clear*/
  do {
    status = read_status(ctrl);
  } while (BSY(status)); 
  
  /*check for errors*/
  status = inb(ctrl->base + REG_STATUS);
  if (status & STATUS_ERR) return -1; //error
  if (status & STATUS_DF)  return -2;//Drive Fault error
  if (!(status & STATUS_DRQ)) return -3; //DRQ must be set
  return 0;
}


void flush_cache(controller_t *ctrl)
{
  outb(CMD_FLUSH, ctrl->base+REG_COMMAND);
  while (is_busy(ctrl));
}

void reset(controller_t *ctrl)
{
  outb(CONTROL_SRST, ctrl->base+REG_CONTROL);
}

/* select a device. see "device selection protocol".
 * To do this before issuing any command to a device(except RESET).
 * drive set the DEV bit in Device/Head register.
 * DEV: when cleared selects device 0, when set selects device 1.
 */
void select_device (controller_t *ctrl, int drive)
{
  unsigned char status;
  /*wait while BSY or DRQ are set*/
  do {
   status = read_status(ctrl);
  } while(BSY(status));
  /*write Device/Head register*/
  outb (0xA0 | (drive<<4), ctrl->base+REG_DRIVE_HEAD);
}

void bl_common (device_t *device , unsigned long lba, int sect_count) 
{
  controller_t *ctrl = device->ctrl;
  if (device->part)
    lba += device->part->s_lba-1; //because using a relative lba
  outb (0xE0 | (device->drive << 4) | ((lba & 0x0F000000)  >> 24), ctrl->base+REG_DRIVE_HEAD); /*the drive indicator, some magic bits, and highest 4 bits of the block address*/
  outb (0x00, ctrl->base+REG_ERROR);	/* NULL byte to port 0x1F1 */
  outb (sect_count, ctrl->base+REG_SECT_COUNT); /*sectors count*/
  outb (lba & 0x000000FF, ctrl->base+REG_LBA_LO); /*LBA low 7:0*/
  outb ((lba & 0x0000FF00) >> 8, ctrl->base+REG_LBA_MI); /*LBA middle 15:8*/
  outb ((lba & 0x00FF0000) >> 16, ctrl->base+REG_LBA_HI); /*LBA high 23:16*/
}
 
/*PIO read.
 * device : drive number(0, 1, 2 or 3)
 *          each IDE controller can handle 2 drives, and most computers have 2 IDE controllers. ).
 * numblock : LBA28 address of the first sector block to read.
 * sect_count : sectors counts to read. Approximatly all ATA-Drives has sector-size of 512-byte.
 * buf : destination
 */
void bl_read (int dev, unsigned long lba, int sect_count, char* buf) 
{
  device_t * device = ide_dev[MINOR(dev)];
  controller_t *ctrl = device->ctrl;
  int i; unsigned char status;
  unsigned char err; char* err_msg;
  
  down (&ctrl->sem);
  ctrl->locker = current;
  select_device (ctrl, device->drive);
  bl_common (device, lba, sect_count);
  outb (0x02, ctrl->base + REG_CONTROL);/*nIEN bit cleared, interrupts enabled*/
  /*read command using LBA28*/
  outb (CMD_READ_LBA28, ctrl->base + REG_COMMAND); 
  
  /*read data*/
  for (i = 0; i < sect_count; i++) {
    delay_400ns(ctrl);
    /* polling status until BSY bit clear*/
    do {
      status = read_status(ctrl);
    } while (BSY(status)); 
  
    /*check for errors*/
    status = inb(ctrl->base + REG_STATUS);
    if (status & STATUS_ERR) goto pior_error; //error
    else if (status & STATUS_DF) {
      warn ("Drive Fault error");
      goto pior_done;
    }
    else if (!(status & STATUS_DRQ)) {
      warn ("DRQ must be set!");
      goto pior_done; 
    }
    /*now we can read a sector*/
    __asm__ (
          "cld \n\t"
          "rep insw"::"c"(SECTOR_SIZE/2), "D"(buf+i*SECTOR_SIZE), "d"(ctrl->base + REG_DATA):);
  }
  goto pior_done;
pior_error:
  err = inb(ctrl->base+REG_ERROR);
  err_msg = ata_error(err);
  warn("error: %s while reading lba %d", err_msg, lba);
  goto pior_done;
pior_done:
  ctrl->locker = NULL;
  up (&ctrl->sem);
}
  
/*blocks read*/
void ide_read (dev_t dev, unsigned long lba, int size, char* buf)
{
  int sect_count;
  char* bl_buf;
  
  sect_count = (size / SECTOR_SIZE) + ((size % SECTOR_SIZE)?1:0);
 
  if (size % SECTOR_SIZE) {
    bl_buf = (char*) kmalloc (sect_count*SECTOR_SIZE, GFP_KERNEL);
    bl_read (dev, lba, sect_count, bl_buf);
    memcpy (bl_buf, buf, size); 
    kfree (bl_buf);
  }
  else
    bl_read (dev, lba, sect_count, buf);
    
}

void ide_write () {
}

void show_atainfo (struct ataid *atainfo)
{
  int i;
  char tmp[64];
  printk ("Hard Drive info:\n");
  if (!(atainfo->gen_conf & 0x8000))
    printk (" ATA device\n");
  if (atainfo->gen_conf & 0x0080)
    printk (" removable media device\n");
  strncpy((char*)&atainfo->serial[0], &tmp[0], 20);
  printk (" serial number: %s\n", &tmp[0]);
  strncpy((char*)&atainfo->model[0], &tmp[0], 40);
  printk (" model: %s\n", &tmp[0]);
  printk (" total number of addressable sectors: %d\n", atainfo->total_sect);
  /*major version*/
  for (i=5; i <= 7; i++)
    if (atainfo->major_version & (1 << i))
      printk (" supports ATA/ATAPI-%d\n", i); 
  if (atainfo->major_version & (1 << 8))
    printk (" supports ATA8-ACS\n"); 
  if (atainfo->major_version & (1 <<  9))
    printk (" supports ACS-2\n"); 
  if (atainfo->major_version & (1 <<  10))
    printk (" supports ACS-3\n"); 
}

/*drive : 0 for master, 1  slave
 */
device_t *probe_a_drive (controller_t *ctrl, int drive)
{
  device_t *device;
  select_device (ctrl, drive);
  delay_400ns(ctrl);
  outb(0x0, ctrl->base+REG_SECT_COUNT);
  outb(0x0, ctrl->base+REG_LBA_LO);
  outb(0x0, ctrl->base+REG_LBA_MI);
  outb(0x0, ctrl->base+REG_LBA_HI);
  outb(CMD_IDENTIFY, ctrl->base+REG_COMMAND);
  delay_400ns(ctrl);
  if (read_status(ctrl) == 0) /*drive not exist*/
    return 0;
  while (is_busy(ctrl)); //polling status until BSY clear
  if (inb(ctrl->base+REG_LBA_MI) || inb(ctrl->base+REG_LBA_HI)) {
    //printk("  Warning, controler base=%#x drive=%d is not ATA\n",ctrl->base, drive);
    return NULL;
  }
  while (!(read_status(ctrl) & (STATUS_DRQ | STATUS_ERR)));//continue polling status until drq or err bits are set
  if (read_status(ctrl) & STATUS_ERR)
    return NULL;
  device = (device_t *)kmalloc(sizeof(device_t), GFP_KERNEL);
  /*Read 256 16-bit values, these contains identify infos*/
  __asm__ (
          "cld \n\t"
          "rep insw"::"c"(256), "D"(&device->atainfo), "d"(ctrl->base+REG_DATA):);
  return device;
}

void probe_drives ()
{
  int err, i, drv;
  device_t *device;
  controller_t* ctrl;
  
  info ("probing IDE devices...");
  for (i=0; i<2; i++) {
    ctrl = &controllers[i];
    for (drv=0; drv<2; drv++) {
      device = probe_a_drive(ctrl, drv);
      if (device) {
        device->major = IDE_MAJOR;
        device->minor = HDA_MINOR + ctrl->id*2 + drv;
        device->ctrl = ctrl;
        device->drive = drv;
        device->name[0] = 'h';
        device->name[1] = 'd';
        device->name[2] = 'a' + ctrl->id*2 + drv;
        device->name[3] = '\0';
        device->part    = NULL;
        err = register_ide_device (device);
        if (err < 0)
           panic ("cannot register partition");
        info ("Detected %s with major=%d minor=%d.", &device->name[0], device->major, device->minor);
        show_atainfo (&device->atainfo);
      }
    }
  }
}

void scan_partitions (device_t * device) 
{
  int i, err;
  device_t *tmp;
  char *buf;
  dev_t dev;
  
  buf = (char*) kmalloc (SECTOR_SIZE, GFP_KERNEL);
  dev = MKDEV(device->major, device->minor);
  ide_read (dev, 0, SECTOR_SIZE, buf);
  
  partition_t *parts = (partition_t *)kmalloc(sizeof(partition_t)*4, GFP_KERNEL);
  memcpy(buf + PARTITION_TABLE_OFFSET, (char*)parts, sizeof(partition_t)*4);
  device->part = parts;
  for (i=0; i < 4; i++) {
    partition_t *part = parts + i;
    if (part->id > 0) {
      tmp = (device_t *)kmalloc(sizeof(device_t), GFP_KERNEL);
      *tmp = *device;
      tmp->part = part;
      tmp->name[3] = i + 1 + '0';
      tmp->name[4] = '\0';
      tmp->minor = (device->minor+1)*16 + i ;
      err = register_ide_device (tmp);
      if (err < 0)
        panic ("cannot register partition");
      info (" |_ %s, major:%d, minor:%d, starting lba:%d, total sectors:%d", &tmp->name[0], tmp->major, tmp->minor,part->s_lba, part->size );
    }
  }
  kfree (buf);
}

void controller_init ()
{
  controller_t *ctrl;
  ctrl = &controllers[PRIMARY_CTRL];
  sem_init (&ctrl->sem, 1);
  ctrl = &controllers[SECONDARY_CTRL];
  sem_init (&ctrl->sem, 1);
}

/* Detect whether controllers are present(modern mothercard may have 2 controllers)
 * then Detect if an ide device is attached to the controller.
 */
void hd_init () 
{
  controller_init();
  probe_drives();
  device_t *hda = ide_dev[HDA_MINOR];
  scan_partitions(hda); 
  root_dev = ROOT_DEV;
  info ("ROOT device is %s", &ide_dev[MINOR(root_dev)]->name[0]);
}

void ide_handler (int ctrlid)
{
  controller_t *ctrl = &controllers[ctrlid];
  wakeup(ctrl->locker);
}
	
	
	
	




