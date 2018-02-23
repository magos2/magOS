/*
** Copyright 2016 @AR
**
**
**
*/

extern void system_call(void);

#include <types.h>
#include <idt.h>
#include <kernel.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ptrace.h>
#include <mm.h>
#include <console.h>
#include <sched.h>
#include <wait.h>
#include <fs.h>
#include <console.h>

#define DEC_SYSC(name)  int sys_##name(unsigned long esp);

DEC_SYSC(restart)
DEC_SYSC(exit)
DEC_SYSC(fork)
DEC_SYSC(execv)
DEC_SYSC(console_write)
DEC_SYSC(console_read)
DEC_SYSC(wait)
DEC_SYSC(uname)
DEC_SYSC(setup)
DEC_SYSC(ls)
DEC_SYSC(cd)
DEC_SYSC(pwd)
DEC_SYSC(ps)
DEC_SYSC(free)
DEC_SYSC(clear)

typedef int (*sys_fn_ptr)(unsigned long);

#define E_SYSC(name)  [SYS_##name]=&sys_##name

sys_fn_ptr sys_call_table[] = {[SYS_restart]=&sys_restart, [SYS_exit]=&sys_exit, [SYS_fork]=&sys_fork, [SYS_execv]=&sys_execv, 
                               [SYS_console_write]=&sys_console_write, [SYS_console_read]=&sys_console_read,
                               E_SYSC(wait), 
                               E_SYSC(uname), E_SYSC(setup), E_SYSC(ls), E_SYSC(cd), E_SYSC(pwd),
                               E_SYSC(ps), E_SYSC(free), E_SYSC(clear)
                              };

int sys_restart(unsigned long esp)
{
  return -ENOSYS;  /* Function not implemented */
}

int sys_exit(unsigned long esp)
{
  do_exit();
  return 0;
}

int sys_fork(unsigned long esp)
{
  return (int)do_fork((struct pt_regs *)esp);
}

int sys_execv(unsigned long esp)
{
  char buf[256];
  char *filename = (char *)(*(unsigned long*)(esp + _EBX));
  strncpy(filename, &buf[0], 256); /*copy str from user to kernel space*/
  do_execv(&buf[0], (struct pt_regs *)esp);
  return 0;
}

int sys_console_write(unsigned long esp)
{
  struct pt_regs* regs;
  char buf[256];
  regs = (struct pt_regs*)esp;
  char *s = (char *)regs->ebx;
  strncpy(s, &buf[0], 256); /*copy str from user to kernel space*/
  printk(&buf[0]);
  return 0;    
}

int sys_console_read(unsigned long esp)
{
  struct pt_regs* regs;
  regs = (struct pt_regs*)esp;
  char *buf = (char *)regs->ebx;
  cons_read(buf);
  return 0;    
}

int sys_wait(unsigned long esp)
{
  do_wait();
  return 0;
}

int sys_ls(unsigned long esp)
{
  do_ls();
  return 0;
}

int sys_cd(unsigned long esp)
{
  struct pt_regs* regs;
  char namebuf[256];
  regs = (struct pt_regs*)esp;
  char *arg1 = (char *)regs->ebx;
  strncpy(arg1, &namebuf[0], 256); /*copy str from user to kernel space*/ 
  do_cd(&namebuf[0]);
  return 0;    
}

int sys_pwd(unsigned long esp)
{
  do_pwd();
  return 0;
}

int sys_ps(unsigned long esp)
{
  do_ps();
  return 0;
}

int sys_free(unsigned long esp)
{
  show_mem();
  return 0;
}

int sys_clear(unsigned long esp)
{
  cons_clear(current->tty);
  return 0;
}


int sys_setup(unsigned long esp)
{
  printk("Appel sys_setup\n");
  return 0;    
}

int sys_uname(unsigned long esp)
{
  printk("Appel sys_uname\n");
  return 0;    
}

void sys_call_init(void)
{
  set_system_gate(0x80, (u32) system_call);
}
