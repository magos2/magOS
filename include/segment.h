#ifndef _SEGMENT_H
#define _SEGMENT_H

#define NR_TASKS 10

#define _BOOT_CS    0x08
#define _BOOT_DS    0x10

#define KERNEL_CS   0x8
#define KERNEL_DS   0x10
#define USER_CS     0x1B /*0x18+3 car user RPL=3*/
#define USER_DS     0x23 
#define DEFAULT_TSS 0x2b /*0x28+3 car user mode*/  

#define sel_idx(selector)  (selector >> 3)  /*selector index on 13 bits 15..3*/

#define PAGE_OFFSET 0xc0000000 /*=3GB. user space(3GB) from 0 to 3GB. kernel space(1GB): from 3GB to 4GB*/

#define KERNEL_STACK 0x8FF00+PAGE_OFFSET /*kernel stack start at 0x8ff00(576k), attention a l'ecrasement des 
                                           params dans le start_kernel */

#define USER_STACK (PAGE_OFFSET - 16)

#endif
