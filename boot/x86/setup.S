/* Copyright 2016 @AR
 *
 * setup.S :
 *   - get machine info(cpu/ram) and store them at 0x90000.
 *   - initialize the Boot GDT 
 *   - switch  cpu to protected mode(PE)
 *   - jump to head.S:startup_32(at 0x1000)
 */

#include <config.h>
#include <segment.h>

SYSADDR = (SYSSEG * 16)   

.att_syntax noprefix
.code16
.global setup_start

setup_start:
   movw  $SETUPSEG, ax
   mov ax, ds
   mov ax, es
   mov ax, ss
   movw $0xfb00, sp # stack of FFFF(~64ko), from 0x9fb00 to 0x90200

/* Saved infos :
 * Memory      Length      Name     
 * 0x90000     2           cursor
 * 0x90002     2           extend memory array from 1MB position
 * 0x90004     2           display page
 * 0x90006     1           display mode
 * 0x90007     1           char column   
 * 0x90008     2           ??
 * 0x9000A     1           display memory(0x00-64k,0x01-128,0x02-192k,0x03=256k)
 * 0x9000B     1           display state(0x00-color I/O=0x3dX; 0x01-monochrome,I/O=3bx)
 * 0x9000C     2           parameter
 * . . .                   ??
 * 0x90080     16          first disk parameter
 * 0x90090     16          second disk parameter
 * 0x901FC     2           root_dev
 */
save_infos:
   movw $INITSEG, ax
   mov ax, ds
   
   #read cursor position
   movb $0x03, ah
   movb $0x00, bh
   int $0x10
   movw dx, 0

   #Extended memory size determination
   movb $0x88, ah
   int $0x15
   movw ax, 2 #number of contiguous 1k blocks of memory starting at address 1MB    
   
   #root_dev
   
# reset data segment to SETUPSEG
   movw $SETUPSEG, ax
   mov ax, ds

/* Enable protected Mode */
activate_pe: 
# calcul  de GDTR
   mov ds, bx
   mov $gdt_boot, ecx
   call calc_adr
   mov eax, gdtr_boot+2
# Passage en mode protege : CR0.PE=1
   cli
   lgdt (gdtr_boot)
   mov cr0, eax
   or $1, eax
   mov eax, cr0
   
   #enable A20
   inb   $0x92, al	# open A20 line(Fast Gate A20).
   orb   $0x02, al 
   outb  al, $0x92
	
   jmp flush_instr

flush_instr:
   mov $_BOOT_DS, ax
   mov ax, ds
   mov ax, es
   mov ax, fs
   mov ax, gs
   mov ax, ss
   mov $0x9fb00, esp
   jmp $_BOOT_CS, $SYSADDR      #jump to the kernel

# --------------------------------
# calc_adr : calcul l'adresse lineaire en mode reel 
#     Entrees : segment -> bx
#               offset -> cx      
#     Sortie : adr -> ax = bx*16 + cx
calc_adr:
   xor eax, eax
   mov bx, ax
   shl $4, eax
   and $0x0000ffff, ecx
   add ecx, eax
   ret 

# GDT de Boot
# GDT descriptor 64 bits:
# |base:8|flags:4|limit hi:4|access:8|base mi:8|base low:16|limit low:16|
# 63--------------------------------------------31----------------------0
gdt_boot:
   .word 0, 0, 0, 0 # reserved
   
    # code entry
   .word 0xFFFF   # limit=0xFFFFF=1M*4kB=4GB
   .word 0x0000   # base=0x0
   .word 0x9B00   # code r/exec
   .word 0x00CF   # granuality 4096(4k)
   
    # data entry
   .word 0xFFFF   # limit=0xFFFFF=4GB
   .word 0x0000   # base=0x0
   .word 0x9300   # data r/w
   .word 0x00CF   # granularity 4096(4k)
gdt_boot_end:

# GDTR Pointer
gdtr_boot:
   .word gdt_boot_end - gdt_boot  # limit(16 bits)
   .long 0x0  # base address(32 bits)

   
setup_end:
.org 2044      # 4 sectors
   .ascii "ANAS"
.end
