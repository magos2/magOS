/* Copyright 2016 @AR
 *
 * head.S contains the 32-bits startup code.
 * it initialise :
 *   idt : at _idt (256 entries of 4B)
 *   gdt : at _gdt
 *   swapper_pg_dir:  the main page directory
 *   pgtable0 : the first page table. identity mapping on 0-4MB.
 *   page 0 is special, all flag set to 0, so to catch derefenced pointers
 * then it :
 *   activate paging by setting CR0.PG bit. cr3 point on swapper_pg_dir 
 *   jump to main.c:start_kernel
 * Notes :
 * breakpoints dont work properly if  base address(in GDT) is not 0x0.(see fixme)
 */
.att_syntax noprefix
.code32

#include <config.h>
#include <segment.h>

.text
.global startup_32
.global _idt, _idtr, _gdtr, _gdt , swapper_pg_dir, pgt0, pgt1
.extern start_kernel, save_mbi

startup_32:
  cld
  cli
  
  #save multiboot info on a secure place
  #eax: contains magic set by grub
  #ebx: points to multiboot info
  push ebx
  push eax 
  call save_mbi

  call setup_paging
  call setup_gdt
  call setup_idt
  
  /* reInitialize eflags.  Some BIOSs leave bits like NT set.  This would
  * confuse the debugger if this code is traced.
  */
  pushl $0
  popfl
 
  # Invalidate the TLB cache
  #mov cr0, eax
  #mov eax, cr0

  movl $KERNEL_DS, eax
  mov ax, ds
  mov ax, es
  mov ax, fs
  mov ax, gs
  ljmp $KERNEL_CS, $1f #flush the processor's instruction prefetch queue 
1: 
  # stack setup
  movl $KERNEL_DS, eax
  mov ax, ss
  movl $KERNEL_STACK, esp
 
  jmp start_kernel   # que fait il penible...!!  

  
setup_idt:
  mov $desc_ignore_int, ebx  # desc_ignore_int.offset = ignore_int
  mov $ignore_int, eax     
  movw ax, (ebx)
  shrl $16, eax
  movw ax, 6(ebx)
  
  xor ecx, ecx       
  mov desc_ignore_int, eax
  mov desc_ignore_int+4, edx
  mov  $_idt, ebx
for_each_idt:             # idt[i]=desc_ignore_int for all 256 interrupts
  mov eax, (ebx, ecx, 8)
  mov edx, 4(ebx, ecx, 8)
  inc ecx
  cmpl $256, ecx
  jb for_each_idt
  
  lidt (_idtr)  
  ret

/* initialise pgtable0 to identity mapping 0-4MiB
 * initilialise the main page directory
 * CR3 is loaded with the physical address of the page directory
 * activate paging : CR0.PG=1
 */
setup_paging:
  call init_pgtable0
  call init_swapper_pg_dir
  mov $swapper_pg_dir-PAGE_OFFSET, eax
  mov eax, cr3
  mov cr0, eax
  orl $0x80000000, eax 
  mov eax, cr0
  ret
  
setup_gdt:
  lgdtl (_gdtr)    #load the new gdt   
  ret
      
/*identity mapping on 0-4MiB in pgtable0.
 * page0 is nulled to catch Nullpointers in kernel code.
 */
init_pgtable0:
  mov $pgtable0-PAGE_OFFSET, ebx   
  movl $0, (ebx)        /*page 0, access(us=0, rw=0, present=0), to catch Nullpointers.*/
  movl $1, ecx
  movl $4096, eax  
  orl $0x3, eax         /*access(us=0, rw=1, present=1)*/
1:
  mov eax, (ebx, ecx, 4)  /* pgtable0[i] = 4096*i + 3(access rw) */
  addl $4096, eax      
  inc ecx
  cmpl $1024, ecx
  jb 1b
  ret

init_swapper_pg_dir:
  /*clear page directory*/
  xor eax, eax     
  mov  $swapper_pg_dir-PAGE_OFFSET, edi
  movl $1024, ecx 
  rep stosl
  
  /*identity mapping on 0-4M. pgdir[0]=pgdir[768]=pgtable0*/
  mov $swapper_pg_dir-PAGE_OFFSET, ebx
  mov $pgtable0-PAGE_OFFSET, eax  
  orl $0x3, eax                    #access(us=0,rw=1,present=1) 
  mov eax, (ebx)
  movl $768, ecx
  mov eax, (ebx, ecx, 4)
  ret
  
ignore_int:
  iret

.data
.align 4
desc_ignore_int:
  .word 0          #offset low
  .word KERNEL_CS  #selector
  .word 0x8E00     #type INTGATE  
  .word 0          #offset high 

## IDT
.align 4 
_idtr:
  .word 256*8  #limit 
  .long _idt

_idt:
  .fill 256,8,0
  
## GDT
.align 4
_gdtr:
	.word NR_TASKS*8-1        #limit
	.long _gdt    #gdt location(linear address),

# GDT descriptor 64 bits:
# |base:8|flags:4|limit hi:4|access:8|base mi:8|base low:16|limit low:16|
# 63--------------------------------------------31----------------------0  
# Access : |present:1|DPL:2|1|exec:1|dc:1|rw:1|ac:1|
# Flags  : |granularity:1|sz:1|0|0|
# see : http://wiki.osdev.org/Global_Descriptor_Table
.macro ADD_DESC base, limit, access, flags
  .word \limit & 0xffff
  .word \base  & 0xffff
  .byte (\base & 0x00ff0000) >> 16
  .byte \access
  .byte ((\flags & 0x0f) << 4) | ((\limit & 0xf0000) >> 16)
  .byte (\base & 0xff000000) >> 24
.endm
.align 4
_gdt:        #6 entries=48B, only used in construction of gdt table at GDT_BASE
  .quad 0x0    #null
  
  ADD_DESC  0x0, 0xfffff, 0x9a, 0xc  #kernel cs, 0-4GiB, dpl=0, exec
  ADD_DESC  0x0, 0xfffff, 0x92, 0xc  #kernel ds, 0-4GiB, dpl=0, r/w
  ADD_DESC  0x0, 0xfffff, 0xfa, 0xc  #user cs, 0-4GiB, dpl=3, exec
  ADD_DESC  0x0, 0xfffff, 0xf2, 0xc  #user ds, 0-4GiB, dpl=3, r/w
  
  .quad 0x0    #default tss
  
  .fill NR_TASKS-6,8,0
_gdt_end:

.org 0x1000
swapper_pg_dir:
  
.org 0x2000
pgtable0:

.org 0x3000
_bad_empty_pgtable1:


.org 0x4000
_bad_empty_pgtable2:



.end


