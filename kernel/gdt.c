#include "libc.h"
#include "types.h"
#include "segment.h"
#include "mm.h"
#include "sched.h"
#define _GDT_
#include "gdt.h"

extern struct gdt_desc _gdt[NR_TASKS]; /*see Head.S*/
extern struct gdtr_desc _gdtr; 

struct tss_struct default_tss = { 
                              0, /*link*/
                              KERNEL_DS, KERNEL_STACK, /* esp0,ss0*/ 
                              0, 0, 0, 0, /*esp1,ss1,esp2,ss2*/
                              0, /*FIXME cr3*/
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* eip,...,edi */
                              0, 0, 0, 0, 0, 0,  /* es,cs,ss,ds,fs,gs*/
                              0,0 /*ldt,iopb*/
                           };

void init_gdt_desc(u32 limit, u32 base, u8 access, u8 flags, struct gdt_desc *s_gdt)
{
   s_gdt->limit_lo = (limit & 0xffff);
   s_gdt->base_lo = (base & 0xffff);
   s_gdt->base_mi = (base >> 16) & 0xff;
   s_gdt->access = access;
   s_gdt->limit_hi = (limit >> 16) & 0xf;
   s_gdt->flags = flags;
   s_gdt->base_hi = (base >> 24) & 0xff;
}

void load_default_tss()
{
   init_gdt_desc(sizeof(struct tss_struct), (u32)&default_tss, 0xE9 , 0x40, &_gdt[sel_idx(DEFAULT_TSS)]);
   // load task register
   __asm__("movw %0, %%ax \n\t"
           "ltr %%ax"::"i"(DEFAULT_TSS));
}



