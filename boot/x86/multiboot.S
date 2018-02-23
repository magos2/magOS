# Multiboot1 header. Needed by Grub2, this must be put on the top of kernel.elf. 
#
.att_syntax noprefix
.code32
#define ASM_FILE
#include <multiboot.h>
MAGIC    = 0x1BADB002
FLAGS    = (MULTIBOOT_INFO_MEMORY | MULTIBOOT_INFO_BOOTDEV)
CHECKSUM = -(MAGIC + FLAGS)

#include <segment.h>

#define MBOOT_STACK 0x4000 /*16kB boot stack*/

.extern startup_32


#the bootloader will search this signature in the first 8kB. the multiboot header
#must be ligned at 32-bit boundary.
.section .multiboot 
.align 4 
mboot_header:
  .long MAGIC
  .long FLAGS
  .long CHECKSUM

.text
#_start = __start - PAGE_OFFSET
.global _start, __start
_start:
  #the bootloader has loaded the kernel into 32-bit protected mode. Interrupts disabled.
  #Paging disabled.
  movl $0x2f4b2f4f, 0xb8000 /*print OK on screen*/
  
  #
  #Magos is a higher half kernel, we must mappe higher addresses. we reserve a page directory,
  #with 4MiB page size(PSE), dont need a page table.
  #set identity mapping on the first 4MB. flags : present, supervisor, r/w, 4MB pages.
  #
  movl $0x00000083, edx         
  mov edx, (boot_pgdir - PAGE_OFFSET)
  movl edx, (boot_pgdir + 768*4 - PAGE_OFFSET)
  #enabling PSE(4MB pages)
  mov cr4, edx
  orl $0x00000010, edx
  mov edx, cr4
  #enable paging. 
  mov $boot_pgdir - PAGE_OFFSET, edx
  mov edx, cr3
  mov cr0, edx
  orl $0x80000000, edx
  mov edx, cr0
   
  #the bootloader does not define a kernel stack(esp), it is up to thr kernel to set up
  #a room for it.
  mov $(mbstack + MBOOT_STACK), esp
  lea 1f, edx
  jmp *edx
1:
  jmp startup_32
  
.section .data
.org 0x1000
boot_pgdir:
  .fill 1024, 4, 0
  
#reserve 16k for boot stack, in data space.
.align 16
.comm mbstack, MBOOT_STACK