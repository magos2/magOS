#ifndef _IDE_H
#define _IDE_H

#include <types.h>
#include <sched.h>
#include <semaphore.h>

#define SECTOR_SIZE 512 

/*channels*/
#define PRIMARY_CTRL   0 /*primary controler*/
#define SECONDARY_CTRL 1

/*4th bit in drive/head register*/
#define MASTER_DRIVE 0
#define SLAVE_DRIVE  1

#define PRIMARY_CTRL_BASE    0x1F0 /*primary controler base*/
#define SECONDARY_CTRL_BASE  0x170

/*ata registers*/
#define REG_DATA       0  /*Read/Write PIO data bytes on this port(base+0).*/
#define REG_ERROR      1
#define REG_SECT_COUNT 2
#define REG_LBA_LO     3
#define REG_LBA_MI     4
#define REG_LBA_HI     5
#define REG_DRIVE_HEAD 6 /*Drive/Head register.*/
#define REG_STATUS     7  /*status register, 0x1F7 or 0x177*/
#define REG_ALT_STATUS 0x206 /*read only. Alternate status register is 0x3F6 for primary*/
#define REG_COMMAND    REG_STATUS
#define REG_CONTROL    0x206 /*write only. Control register is 0x3F6 for primary*/

/*list of commands*/
#define CMD_FLUSH        0xE7
#define CMD_IDENTIFY     0xEC
#define CMD_READ_LBA28   0x20
#define CMD_WRITE_LBA28  0x30  /*???*/

/*Status bits, read from status register*/
#define STATUS_ERR 0x00  /*bit 0, indicates an error occurred. Send a new command to clear it*/
#define STATUS_DRQ 0x08  /*the host can read/write data only when this bit is set*/
#define STATUS_SRV 0x10  /*Overlapped Mode Service Request.*/
#define STATUS_DF  0x20  /*Drive Fault Error (does not set ERR).*/
#define STATUS_RDY 0x40  /*Bit is clear when drive is spun down, or after an error. Set otherwise.*/
#define STATUS_BSY 0x80  /*Indicates the controller is busy, and should not be accessed .*/

/*Control Register bits*/
#define CONTROL_nIEN  0x02  /*Set this bit to stop the current device from sending interrupts.*/
#define CONTROL_SRST  0x04  /*Set this bit to do a "Software Reset" on all ATA drives on a bus, if one is misbehaving.*/
#define CONTROL_HOB   0x80  /*Set this bit to read back the High Order Byte of the last LBA48 value sent to an IO port.*/

/*Error Register bits*/
#define ERR_BBK   0x01  /*(Bad Block)*/
#define ERR_UNC   0x02  /*(Uncorrectable data error)*/
#define ERR_MC    0x04  /*(Media Changed)*/
#define ERR_IDNF  0x08  /*(ID mark Not Found)*/
#define ERR_MCR   0x10  /*(Media Change Requested)*/
#define ERR_ABRT  0x20  /*(command aborted)*/
#define ERR_TK0NF 0x40  /*(Track 0 Not Found)*/
#define ERR_AMNF  0x80  /*(Address Mark Not Found)*/

#define ATA_REPEAT_DELAY 5 /*repeat 5 times reading status register, to obtain 400ns detay */

#define NODEV_MAJOR    0
#define FLOPPY_MAJOR   1
#define CDROM_MAJOR    2
#define IDE_MAJOR      3  /*hda,hdb,hdc,hdd*/
#define USB_MAJOR      4

#define IDE_MAXDEV   256
#define IDE_MAXPART   16  /*max partition par hard drive*/

#define HDA_MINOR      0  /*hda minor=0; hda1 minor=16;  hdaX minor=16+X*/
#define HDB_MINOR      1  /*hdb minor=1; hdbX minor=32+X; */
#define HDC_MINOR      2
#define HDD_MINOR      3

#define MAJOR(dev)          ((dev) >> 8)
#define MINOR(dev)          ((dev) & 0xFF)
#define MKDEV(major,minor)  (((major) << 8) | ((minor) & 0xFF))
#define DEVICE(dev)         (ide_dev[MINOR(dev)])	

#define ROOT_DEV  0x0310   /*hda1*/


#define PARTITION_TABLE_OFFSET 446  /*partition table location in the MBR*/

struct partition {
	u8  bootable;		/* 0 = no, 0x80 = bootable */
	u8  s_head;		  /* Starting head */
	u16 s_sector:6;	  /* Starting sector */
	u16 s_cyl:10;		/* Starting cylinder */
	u8  id;			  /* System ID */
	u8  e_head;	  	/* Ending Head */
	u16 e_sector:6;	  /* Ending Sector */
	u16 e_cyl:10;		/* Ending Cylinder */
	u32 s_lba;		   /* Starting LBA value */
	u32 size;		    /* Total Sectors in partition */
} __attribute__ ((packed));

typedef struct partition partition_t;

#define is_bootable(part)  ((part->bootable == 0x80)?1:0)

/*IDENTIFY DEVICE information*/
struct ataid {
#define UNUSED(start,end) unused##start_##end[end-start+1]
  u16 gen_conf;       /* 0*/
  u16 UNUSED(1,1);    /* 1*/
  u16 specific_conf;  /* 2*/
  u16 UNUSED(3,9);    /* 3-9*/
  u16 serial[10];     /* 10-19 serial number 20 chars*/
  u16 UNUSED(20,22);  /* 20-22*/
  u16 firmware[4];    /* 23-26 firmwre revision*/
  u16 model[20];      /* 27-46 model number 40 chars*/
  u16 UNUSED(47,48);  /* 47-48 */
  u32 capabilities;   /* 49-50*/
  u16 UNUSED(51,59);  /* 51-59*/
  u32 total_sect ;    /* 60-61 total number of user adressable sectors*/
  u16 UNUSED(62,62);  /* 62 */
  u16 dma_mode;       /* 63 */
  u16 UNUSED(64,74);  /* 64-74*/
  u16 queue_depth;    /* 75*/
  u16 UNUSED(76,79);  /* 76-79*/
  u16 major_version;  /* 80*/
  u16 minor_version;  /* 81*/
  u16 commandset_feature[6]; /* 82-87 command set/fetures*/
  u16 UNUSED(88,99);         /* 88-99*/
  u16 max_lba48[4]  ;        /* 100-103 maximum lba for 48-bit feature set*/
  u16 UNUSED(104,254);       /* 104-254*/
  u8  signature ;            /* 255*/
  u8  checksum ;  
};

struct controller_struct {
  int id;   /*0 or 1*/
  int base; /*0x1F0 for primary controler, 0x170 for second*/
  int irq;  /*associated to this controler, 14,or 15*/
  task_t *locker;  /*process locking this controller*/
  semaphore_t sem;  /*semaphore pour reveiller les threads en attente sur des operations*/
  int mutex; /*pour controler les acces concurrents*/
};

typedef struct controller_struct controller_t;

struct hd_info {
  int cyl, head, sect;
};

struct device_struct {
  u8 major;
  u8 minor;
  controller_t *ctrl;
  int drive; /*DRV bit in Drive/Head register. 0=master,1=slave*/
  char name[6]; /*hda,hdb(ide),hda1, sda, sdb(sata) fda*/
  int media; /*hd,cdrom,floppy*/
  partition_t *part; /*partition table*/
  struct device_s *next;
  struct ataid atainfo;
};
typedef struct device_struct device_t;


extern dev_t root_dev;
extern struct disk* root_hd;
extern device_t * ide_dev[];

void hd_init ();
void ide_read (dev_t dev, unsigned long lba, int size, char* buf);
unsigned char register_ide_device (device_t *device);
void unregister_ide_device (device_t *device);

#endif
