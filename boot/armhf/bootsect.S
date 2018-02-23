/* Copyright 2016 @AR
 *
 * this is the boot sector. it loads load setup and kernel, and jump to SETUPSEG:0 (0x90200).
 * Le boot sector se deplace  à 0x90000(9000:0000), afin d avoir le plus d espace
 * possible en memoire basse(<1Mo, Low memory).
 */
//include <config.h> /*definition of BOOTSEG,INITSEG,SETUPSEG,SYSSEG*/

sys_size = 100 /*number of kernel sectors  to load, 1 sector=512 Bytes*/

.global _start

// Init the DS and SS
_start:


// --------------------------------
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
   .word 0xAA55  //magic word
.end



