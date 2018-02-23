/* these are ext2 file operations.
 *
 */
#include <ide.h>
#include <ext2.h>
#include <mm.h>
#include <libc.h>
#include <errno.h>
#include <types.h>
#include <file.h>
int ext2_read_file (struct file *fp, char *buf, size_t count);
int ext2_write_file (struct file *fp, char *buf, size_t count);;

struct file_operations ext2_file_ops = {
     .read = ext2_read_file,
     .write = ext2_write_file,
     .ioctl = NULL,
     .mmap = generic_mmap,
     .open = NULL,
     .flush = NULL,
     .release = NULL
     };
     
int ext2_read_file (struct file *fp, char *buf, size_t count)
{
  int i;
  int blocksize;
  int blocknr;
  int n;
  int sz;
  char * mmap;
  char* bl_buf;
  char* i_buf;
  char* bi_buf;
  char* tri_buf;
  struct disk *hd;
  struct ext2_inode * inode;
  
  hd = fp->f_hd;
  inode = fp->f_inode;
  blocksize = hd->blocksize;
  sz = inode->i_size;
  mmap = buf;
  bl_buf = (char *) kmalloc(blocksize, GFP_KERNEL);
  
  /*read direct blocks*/
  n = 0;
  for (i=0; i <= 11; i++) {
    if (inode->i_block[i] > 0) {
      ext2_ide_read (hd, inode->i_block[i], blocksize, bl_buf);
      n = (sz > blocksize)?blocksize:sz;
      memcpy (bl_buf, mmap, n);
      mmap += n;
      sz -= n;
    }
  }
    
  /*read indirect blocks*/
  if (inode->i_block[12] > 0) {
    i_buf = (char *) kmalloc(blocksize, GFP_KERNEL);
    ext2_ide_read (hd, inode->i_block[12], blocksize, i_buf);
    for (i=0; i<256; i++) {
      blocknr = *(i_buf + i*4);
      if (blocknr > 0) {
        ext2_ide_read (hd, blocknr, blocksize, bl_buf);
        n = (sz > blocksize)?blocksize:sz;
        memcpy (bl_buf, mmap, n);
        mmap += n;
        sz -= n;
      }
    }
  }
  /*read bi-indirect blocks*/
  //todo
  if (inode->i_block[13] > 0) {
    bi_buf = (char *) kmalloc(blocksize, GFP_KERNEL);
    ext2_ide_read (hd, inode->i_block[13], blocksize, bi_buf);
  }
  
  
  /*read tri-indirect blocks*/
  //todo
  if (inode->i_block[14] > 0) {
    tri_buf = (char *) kmalloc(blocksize, GFP_KERNEL);
    ext2_ide_read (hd, inode->i_block[14], blocksize, tri_buf);
  }
  
  return 0;
}

int ext2_write_file (struct file *fp, char *buf, size_t count)
{
  return 0;
}
//int open (char *filepath, int prot)
