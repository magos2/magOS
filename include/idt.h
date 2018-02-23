#ifndef _IDT_H
#define _IDH_H

#include "types.h"

#define IDT_SIZE  256    /* 256 entires of 8B = 2k*/

#define TRAPGATE  0x8F00   
#define INTGATE   0x8E00
#define SYSGATE   0xEE00   


void set_trap_gate(u16 n, u32 addr);
void set_intr_gate(u16 n, u32 addr);
void set_system_gate(u16 n, u32 addr);

void idt_init();


#endif
