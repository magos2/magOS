#define KERNEL_DEBUG 0
#include <mm.h>
#include <sched.h>
#include <kernel.h>
#include <fs.h>
#include <file.h>
#include <errno.h>
#include <libc.h>

/*loads a new executable file replacing the current*/ 
void do_execv(char *filename, struct pt_regs *regs)
{
  int fd, err;
  char *buf;
  struct file* fp;
  
  debug("do_execv");
 
  fd = sys_open (filename, 0);
  if (fd < 0) {
    warn("error opening file %s: %s", filename, err_msg(fd));
    return;
  }
  fp = current->filp[fd];
  fp->f_op->mmap (fp);
  buf = (char *)fp->f_vma->vm_start;
  err = sys_read (fd, buf, fp->f_inode->i_size);
  if (err < 0) {
    warn ("error reading file %s:  %s", filename, err_msg(err));
    //close opened file
    return;
  }
  memcpy(buf, (char*)LD_ENTRY, fp->f_inode->i_size);
  regs->xcs = USER_CS;
  regs->xds = regs->xes = regs->xss = USER_DS;
  regs->esp = USER_STACK;
  regs->eip = LD_ENTRY;
  info ("Programm loaded, name=%s inode=%d size=%dB", filename, fp->f_inum, fp->f_inode->i_size);
  debug ("do_execv ok");
}

