#ifndef _GDH_H
#define _GDH_H

#include "types.h"

struct gdt_desc {
   u16 limit_lo;
   u16 base_lo;
   u8  base_mi;
   u8  access;
   u8  limit_hi:4,
       flags:4;
   u8  base_hi;
} __attribute__((packed));

struct gdtr_desc {
   u16 limit;
   u32 base;
} __attribute__((packed));

void init_gdt();
void load_default_tss();

#endif
