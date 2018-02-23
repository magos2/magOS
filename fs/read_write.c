
#include <types.h>
#include <file.h>
#include <errno.h>
#include <kernel.h>
#include <sched.h>


int sys_read (int fd, char* buf, size_t count)
{
  int err;
  if (fd >= MAX_OPEN || count < 0 || !current->filp[fd])
    return -EINVAL; //invalid argument
  struct file * fp = current->filp[fd];
  err = fp->f_op->read(fp, buf, count);
  return err;
}

int sys_write (int fd, char* buf, int count)
{
  struct file * f;
  
  f = current->filp[fd];
  if (fd >= MAX_OPEN || count < 0 || !f)
    return -EINVAL; //invalid argument
  return 0;
}






