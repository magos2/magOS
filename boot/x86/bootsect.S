/* Copyright 2016 @AR
 *
 * this is the boot sector. it loads load setup and kernel, and jump to SETUPSEG:0 (0x90200).
 * Le boot sector se deplace  à 0x90000(9000:0000), afin d avoir le plus d espace
 * possible en memoire basse(<1Mo, Low memory).
 */
#include <config.h> /*definition of BOOTSEG,INITSEG,SETUPSEG,SYSSEG*/

/*syssize in 1KiB, calculated in Makefile. 1 sector=512 Bytes*/
 
.att_syntax noprefix
.code16
.global _start

# Init the DS and SS
_start:

move_self:
   movw $BOOTSEG,ax  #src
   mov ax, ds
   movw $INITSEG, ax  #dest
   mov ax, es
   xor si, si
   xor di, di
   movw $512, cx      #512 bytes to move
   cld
   rep movsb
   
.align 4            #gdb will struggle if bad align!
   jmp  $INITSEG , $go
.align 4
go:
   movw $INITSEG, ax
   mov ax, ds
   mov ax, es
# config de la Pile en FFFF(64ko) : 0x9fB00 -> 0x90000   
   mov ax, ss       
   movw $0xfb00, sp
   
# Bootdrive saving
   movb dl, bootdrive 	

# Effacer l'ecran 
   mov $0x03, ax
   int $0x10
 
# Afficher le message Loding...
.align 4
   mov $msg_load, si
   call display_msg
   

/* load  up the setup-sectors at 0x90200 */
load_setup:
   mov $SETUPSEG, ax  # es:bx is the destination
   mov ax, es
   xor bx, bx
   mov $2, ah         # read function
   mov $SETUPLEN, al  # nr of sectors to load
   mov $0, ch         # cylindre
   mov $2, cl         # start sector 
   mov $0, dh         # head
   mov bootdrive, dl  # 0x80 for hard disk, 0 for floppy
   int $0x13
   jc error_load
   call display_dot

/* load system at 0x10000 from the sector number 5. because 1 sector for bootsector, 4 for setup */
load_sys:
   xor eax, eax
   xor ecx, ecx   
   mov $SYSSEG, ax       # es:bx is the destination
   mov ax, es
   xor bx, bx
   mov $2, ah            # read function
   mov $syssize, al      # nr of sectors to load
   shl $1, al              # syssize is in KiB,
   mov $0, ch            # cylindre
   mov $SETUPLEN+2, cl   # start sector 
   mov $0, dh            # head
   mov bootdrive, dl     # 0x80 for hard disk, 0 for floppy
   int $0x13
   jc error_load
end_load_sys:   
   call display_ok
      
# Jump to setup
   jmp $SETUPSEG, $0
 
# --------------------------------
# display_msg(msg) 
#     Entree : msg -> si
#     Sortie : ecran
display_msg:
   push ax
   push bx
   mov $0x0e, ah
   mov $0x07, bx  
loop_display_msg:
   lodsb 	# [ds:si] -> al
   cmp $0, al
   jz end_display_msg
   int $0x10	# int du Bios
   jmp loop_display_msg
end_display_msg:  
   pop bx
   pop ax
   ret

display_ok:
   leaw msg_ok, si
   call display_msg

# print a "."
display_dot:
   push ax
   push bx
   mov $0x0e, ah       
   mov $'.',  al
   mov $0x07, bx
   int $0x10
   pop bx
   pop ax
   ret
# --------------------------------
error_load:
   #print_nl
   leaw msg_error_load, si
   call display_msg
   jmp halt

#--------------------------------
halt:
   jmp halt
   
# --------------------------------
msg_load : 
   .asciz  "Loading..."

msg_ok :
   .asciz "[OK]"

msg_error_load :
   .asciz "error loading kernel. HALT!"

bootdrive:
   .word 0

.org 510
boot_flag:	
   .word 0xAA55  #magic word
.end



