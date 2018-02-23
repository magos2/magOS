#ifndef _FILE_H
#define _FILE_H

#include <ext2.h>
#include <mm.h>

#define FILE_NAME_LEN 64

struct file {
  struct disk * f_hd;
  unsigned long f_inum;
  struct ext2_inode* f_inode;
  char f_name[FILE_NAME_LEN];
  vm_area_t* f_vma;
  size_t f_size;
  int f_prot;
  
  struct file_operations * f_op;
};

struct file_operations {
  int (*read) (struct file *fp, char *buf, size_t count);
  int (*write) (struct file *fp, char *buf, size_t count);
  int (*ioctl) (struct ext2_inode *ino, struct file *fp, unsigned int, unsigned long);
  int (*mmap) (struct file *fp);
  int (*open) (struct ext2_inode *ino, struct file *fp);
  int (*flush) (struct file *fp);
  int (*release) (struct ext2_inode *ino, struct file *fp);
};

extern struct file_operations ext2_file_ops;





#endif