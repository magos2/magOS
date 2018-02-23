#include <file.h>
#include <fs.h>
#include <ide.h>
#include <kernel.h>
#include <bitops.h>
#include <sched.h>
#include <string.h>

/*search first free fd*/
int get_free_fd () {
  int fd;
  for (fd=0; fd < MAX_OPEN; fd++)
    if (!current->filp[fd])
      return fd;
  return -EMFILE;
}


/* out : fd*/
int sys_open (char * filepath, int mode)
{
  int fd, error;
  struct file* fp;
  
  fd = get_free_fd ();
  if (fd < 0) {
    printk ("too many open files\n");
    return -EMFILE;
  }
  current->filp[fd] = (struct file*)kmalloc(sizeof(struct file), GFP_KERNEL);
  fp = current->filp[fd];
  fp->f_hd = root_hd;
  fp->f_op = &ext2_file_ops;
  error = namei (filepath, mode, fp);
  if (error < 0) 
    return error;
  return fd;
}
  
/*open root directory "/".
 * this function is used only one time, during bootstrap!
 */
struct file* open_root (int mode)
{
  struct file* fp;
  
  int fd = 0; /*let use fd 0 for root directory*/
  current->filp[fd] = (struct file*)kmalloc(sizeof(struct file), GFP_KERNEL);
  fp = current->filp[fd];
  fp->f_hd = root_hd;
  fp->f_op = &ext2_file_ops;
  fp->f_inum = EXT2_ROOT_INO;
  fp->f_inode = ext2_read_inode(root_hd, EXT2_ROOT_INO);
  fp->f_size = fp->f_inode->i_size;
  strncpy("/", &fp->f_name[0], 2);
  return fp;
}