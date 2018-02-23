/* Copyrigth 2016 @AR
** 
** idt.c initialise la table IDT et charge le registre IDTR. 
*/ 

#include "idt.h"
#include "types.h"
#include "segment.h"
#include "libc.h"
#include "traps.h"
#include "irq.h"

struct idt_desc {
   u16 offset_lo;
   u16 selector;
   u16 type;
   u16 offset_hi;
} __attribute__ ((packed));

struct idtr_desc {
   u16 limit;
   u32 addr;
} __attribute__ ((packed));

extern struct idt_desc _idt[IDT_SIZE] ; 
extern struct idtr_desc _idtr;

extern void sys_call_init(void);

void _set_gate (struct idt_desc *gate, u16 type, u32 addr)
{
   gate->offset_lo = (addr & 0xffff);
   gate->selector = KERNEL_CS; 
   gate->type =  type;
   gate->offset_hi = (addr & 0xffff0000) >> 16;  
}

/*interrupt materielles: irq*/
void set_intr_gate(u16 n, u32 addr)
{
   _set_gate(&_idt[n], INTGATE, addr);
}

/* exceptions : page_fault, gpf...*/
void set_trap_gate(u16 n, u32 addr)
{
   _set_gate(&_idt[n], TRAPGATE, addr);
}

/* interrup logicielles int 80h*/
void set_system_gate(u16 n, u32 addr)
{
   _set_gate(&_idt[n], SYSGATE, addr);
}

void idt_init()
{
   trap_init();
   irq_init();
   sys_call_init();
}



