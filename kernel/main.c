/* Copyright 2016 @Abderrahim Rahali
** 
** the kernel entry 
*/
#define KERNEL_DEBUG 0
#include <system.h>
#include <types.h>
#include <segment.h>
#include <kernel.h>
#include <errno.h>
#include <gdt.h>
#include <idt.h>
#include <mm.h>
#include <kernel.h>
#include <unistd.h>
#include <console.h>
#include <ide.h>
#include <ext2.h>
#include <libc.h>
#include <sched.h>
#include <timex.h>
#include <fs.h>
#include <multiboot.h>

extern unsigned long _end;
extern struct task_struct INIT_TASK;

unsigned long start_low_mem = START_LOW_MEM;
unsigned long low_mem;
unsigned long start_mem;
unsigned long end_mem;
extern dev_t root_dev;
extern struct disk* root_hd;

multiboot_info_t mbi;


void start_kernel(void);  
 
/* process #0*/
void cpu_idle(void)
{
  while (1) halt();
}
 
/*process #1 */ 
int init(char *arg1)
{
  pid_t pid;
  
  info("Init Process: pid=%d", current->pid);
  pid = fork();
  if (pid == 0)
    execv("/usr/bin/shell");
  info ("Creation of shell process with pid=%d", pid);
  warn("Process <Init> never end");
  while(1)  halt();
}

void kthreadd()
{
  while(1);
}


  
void start_kernel(void)
{
#ifdef LOCAL_LOADER
  char* psetup = (char *)0x90000; //INITSEG*16
#endif
  char * banner = "Starting MagOS...\n"; 
  
  start_mem = (unsigned long)&_end - PAGE_OFFSET;
  if (start_mem < START_LOW_MEM)
    start_mem = START_LOW_MEM;
  //end_mem = (*((unsigned short *)(psetup+2)))*1024 + 1024*1024; 
  low_mem = mbi.mem_lower*1024;
  end_mem = mbi.mem_upper*1024 + 0x100000;
  end_mem &= PAGE_MASK;
  
  cli();  
  cons_init();
  printk(banner);
  
  start_mem = paging_init(start_mem, end_mem); //kernel pg dir init
  start_mem = mem_init(start_mem, end_mem);    //physical mem
  idt_init();
  _8253_init(); /*timer*/
  sched_init();
  hd_init ();
  
  info ("Meminfo: low memory=%dkB start memory=%dkb end memory=%dmB", 
                    low_mem/1024, start_mem/1024, end_mem/1024/1024);
  
  /*initialize root_dev and root inode*/
  root_hd = ext2_read_disk_info(root_dev);
  if (ext2_check_disk(root_hd) < 0)
    panic ("bad disk, magic word expected %#x, found %#x", EXT2_MAGIC, root_hd->sb->s_magic);
  ext2_display_disk_info (root_hd);
  current->root = current->pwd = open_root(0);
  debug ("ROOT: root_dev=%s, f_size=%d, i_blocks=%d", 
                 DEVICE(root_dev)->name,current->root->f_size,current->root->f_inode->i_blocks);
  
  printk("Welcome to MagOS!\n");
  
  //kernel_thread(&init, NULL);
  
  /*Switch to user mode*/
  load_default_tss();
  pid_t pid = fork();
  if (pid == 0)  //child
     execv("/usr/bin/shell");
  sti(); //go
  cpu_idle(); 
  for (;;)
    continue;

}

/*save multiboot info returned by the bootloader into a secure place. after loading 
 *the kernel, the bootloader transmits some vital infos to kernel:
 *  eax: magic
 *  ebx; pointes to multiboot info
 */ 
void save_mbi (unsigned long magic, multiboot_info_t* _ebx)
{
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC) 
    panic ("this kernel must be loaded by grub2. expected magic %x found %x", MULTIBOOT_BOOTLOADER_MAGIC, magic);
  
  mbi = *(_ebx);

  if (!CHECK_FLAG(mbi,0)) 
    panic ("multiboot flag[0] is expected to be set, but it is not!");
}