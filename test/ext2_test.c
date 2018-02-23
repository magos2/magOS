


#include "ext2.h"
#include <stdio.h>


void ide_read (int device, int numblock, int size, char* buf)
{
}

int main(void)
{
  struct ext2_super_block* sb;
  struct disk *hd;
  
  char* img = "/sdcard1/qemu/qemu.img";
  
  //ext2_read_sb(hd, sb);
}