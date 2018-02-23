#include <fs.h>
#include <ide.h>
#include <ext2.h>
#include <file.h>
#include <errno.h>
#include <sched.h>
#include <kernel.h>
#include <string.h>

char * file_systems [10]; 

char * mount_table[15];


int do_cd(char* path)
{
  int fd, err;
  struct file* fp;
  
  if (strcmp(path, "/") == 0) {
    current->pwd = current->parent->pwd = current->parent->root;
    return 0;
  }
  else if (strcmp(path, ".") == 0) {
    return 0;
  }
  fd = sys_open (path, 0);
  if (fd < 0) {
    warn("error entring directory %s: %s", path, err_msg(fd));
    return -ENOTDIR;
  }
  fp = current->filp[fd];
  if (!IS_DIR(fp->f_inode)) {
  	err = -ENOTDIR;
  	printk ("%s\n", err_msg(err));
      return -ENOTDIR;
  }
  current->pwd = current->parent->pwd = fp;
  /*sys_close(fd)*/
  return 0;
}

int do_ls()
{
  struct ext2_dir_entry * dentry; 
  struct file *pwd;
  char *mmap;
  struct ext2_inode *inode;
  char dname[EXT2_NAME_LEN];
  int err;
  
  pwd = current->pwd;
  err = pwd->f_op->mmap (pwd);
  if (err < 0)
    warn ("do_ls, error  %d", err); 
  mmap = (char *)pwd->f_vma->vm_start;
  err = pwd->f_op->read (pwd, mmap, pwd->f_inode->i_size);
  if (err < 0) 
    return err;
  printk ("name        inode size\n");
  dentry = (struct ext2_dir_entry *)mmap;
  while ((unsigned long)dentry < ((unsigned long)mmap + pwd->f_inode->i_size)) {
    strncpy (&dentry->name[0], &dname[0], dentry->name_len);
    inode = ext2_read_inode(pwd->f_hd, dentry->inode);
    printk ("%12s%6d%6d\n", dname, dentry->inode, inode->i_size);
    kfree(inode);
    dentry = (struct ext2_dir_entry *)((char*)dentry + dentry->rec_len);
  } 
  kfree(mmap);
  kfree(pwd->f_vma);
  return 0;
}

int do_pwd()
{
  struct file* pwd = current->pwd;
  printk ("%s\n", pwd->f_name);
  return 0;
}
	
	
	
	

	
	
	
