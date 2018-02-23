/* Copyright 2016 @AR
 *
 * head.S contains the 32-bits startup code.
 * it initialise :
 *    idt : at 0x0 (256 entries of 4B)
 *    gdt : at 0x400
 *    swapper_pg_dir: at 0x1000. the main page directory
 *    pg0 : at 0x2000. the first page table. identity mapping on 0-4MB.
 * then it :
 *    activate paging by setting CR0.PG bit. cr3 point on swapper_pg_dir 
 *    jump to main.c:start_kernel
 * Notes :
 * breakpoints dont work properly if  base address(in GDT) is not 0x0.(see fixme)
 */

   .text
//include <config.h>
//include <segment.h>

//define PAGING_FLAG (1 << 31) /*CR0, bit 31*/
//define PAGE_OFFSET 0xc0000000 /*=3GB*/


.global startup_32
.global _idt, _idtr, _gdtr, _gdt , swapper_pg_dir, pgt0, pgt1
.extern start_kernel

startup_32:
   

.data
.align 4
desc_ignore_int:
   .word 0          //offset low
   .word 18  //selector
   .word 0x8E00     //type INTGATE  
   .word 0          //offset high 

//// IDT
.align 4 
_idtr:
   .word 256*8   //limit 
   .long _idt

_idt:
   .fill 256,8,0
   
//// GDT
.align 4
_gdtr:
	.word 48      //limit
	.long _gdt      //gdt location(linear address),

// GDT descriptor 64 bits:
// |base:8|flags:4|limit hi:4|access:8|base mi:8|base low:16|limit low:16|
// 63--------------------------------------------31----------------------0   
.align 4
_gdt:            //6 entries=48B, only used in construction of gdt table at GDT_BASE
   .quad 0x0     //null
   
   .word 0xffff  //kernel CS : 1GiB. base=3GiB=0xC0000000 limit=0x3ffff=1GiB
   .word 0x0000
   .word 0x9a00  //code r/w/x
   .word 0x00cf  //0xc0c3, fixme qemu/gdb base=0x0
   
   .word 0xffff  //kernel DS : 1GiB
   .word 0x0000
   .word 0x9200  //data r/w
   .word 0x00cf  //0x00c3, fixme qemu/gdb base=0x0
   
   .word 0xffff  //user CS : 3GB - base=0x0 limit=0xbffff=3GiB
   .word 0x0000
   .word 0xfa00
   .word 0x00cf 
   
   .word 0xffff  //user DS : 0-3GB
   .word 0x0000
   .word 0xf200
   .word 0x00cf
   
   .quad 0x0     //default tss
   
_gdt_end:

.org 0x1000
swapper_pg_dir:
   
.org 0x2000
pgt0:

.org 0x3000
_bad_empty_pgt1:


.org 0x4000
_bad_empty_pgt2:



.end


