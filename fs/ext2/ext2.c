/* Copyright 2016 @AR
 *
 * EXT2 File system.
 * 
 */
#define KERNEL_DEBUG 0
#include <ide.h>
#include <ext2.h>
#include <mm.h>
#include <libc.h>
#include <errno.h>
#include <kernel.h>

#define DIV2(a,b)  ((a) / (b) + (((a) % (b))?1:0))


void ext2_ide_read (struct disk *hd, unsigned long numblock, int size, char* buf)
{
  unsigned long lba;
  lba = (numblock * hd->blocksize) / SECTOR_SIZE;
  ide_read (hd->dev, lba, size, buf);
}

int ext2_read_sb (struct disk *hd, struct ext2_super_block* sb)
{
  ide_read (hd->dev, 2, sizeof(struct ext2_super_block), (char*)sb); /*lba=2 sectors, cad lba=1024B*/
                                                                     /*we cannot use ext2_ide_read, we dont know blocksize yet*/
  return 0;
}

int ext2_read_gd (struct disk *hd,  struct ext2_group_desc* gd)
{
  int gd_size = hd->groups*sizeof(struct ext2_group_desc);
  ide_read (hd->dev, 4, gd_size, (char*)gd);
  //char buf[512];
  //ide_read(0x101, 4, 512, &buf[0]);
  return 0;
}

int ext2_check_disk (struct disk *hd)
{
  if (hd->sb->s_magic != EXT2_MAGIC)
	  return -EBADF;
  return 0;
}

struct disk * ext2_read_disk_info (dev_t dev)
{
  struct disk *hd;
  struct ext2_super_block* sb;
  struct ext2_group_desc* gd;
  
  hd = (struct disk *)kmalloc(sizeof(struct disk), GFP_KERNEL);
  hd->dev = dev;
  sb = (struct ext2_super_block *)kmalloc(sizeof(struct ext2_super_block), GFP_KERNEL);
  ext2_read_sb (hd, sb);
  hd->sb = sb;
  
  hd->blocksize = (1024 << sb->s_log_block_size);
  
  hd->groups = DIV2 (sb->s_blocks_count, sb->s_blocks_per_group);
  
  gd = (struct ext2_group_desc *)kmalloc(hd->groups*sizeof(struct ext2_group_desc), GFP_KERNEL);
  ext2_read_gd (hd, gd);
  hd->gd = gd;
  
  return hd;
}

void ext2_display_disk_info (struct disk *hd)
{
  struct ext2_group_desc *gd0 = hd->gd + 0;
  info ("PartitionInfo");
  printk ("      %s ", DEVICE(hd->dev)->name);
  printk ("[%d inodes %d blocks %dB blocksize. ", hd->sb->s_inodes_count, hd->sb->s_blocks_count, hd->blocksize);
  printk ("group #0 contains %d dirs]\n", gd0->bg_used_dirs_count);
}

struct ext2_inode* ext2_read_inode (struct disk *hd, int inum) 
{
  int i , inodes_per_block, inum_in_block;
  unsigned long inode_block;
  struct ext2_inode* inode, *inotable_buf;
  struct ext2_group_desc* gd;
  
  //the group to wich the inode belong
  i =  (inum-1) / hd->sb->s_inodes_per_group;
  gd = hd->gd + i;
  inodes_per_block = hd->blocksize / sizeof(struct ext2_inode);
  inode_block = gd->bg_inode_table + (inum - 1) /  inodes_per_block;
  inum_in_block = (inum - 1) % inodes_per_block;
  inotable_buf = (struct ext2_inode *) kmalloc(hd->blocksize, GFP_KERNEL);
  /*read one block in inode_table, this block contains inode <inum>*/
  ext2_ide_read(hd, inode_block, hd->blocksize, (char*)inotable_buf);
  inode = (struct ext2_inode *) kmalloc(sizeof(struct ext2_inode), GFP_KERNEL);
  *inode = *(inotable_buf + inum_in_block);
  kfree(inotable_buf);
  return inode;
}



















