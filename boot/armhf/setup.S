/* Copyright 2016 @AR
 *
 * setup.S :
 *   - get machine info(cpu/ram) and store them at 0x90000.
 *   - initialize the Boot GDT 
 *   - switch  cpu to protected mode(PE)
 *   - jump to head.S:startup_32(at 0x1000)
 */

//include <config.h>
//include <segment.h>

//SYSADDR = (SYSSEG * 16)   

.global setup_start

setup_start:
   

// GDT de Boot
// GDT descriptor 64 bits:
// |base:8|flags:4|limit hi:4|access:8|base mi:8|base low:16|limit low:16|
// 63--------------------------------------------31----------------------0
gdt_boot:
   .word 0, 0, 0, 0 // reserved
   
    // code entry
   .word 0xFFFF   // limit=0xFFFFF=1M*4kB=4GB
   .word 0x0000   // base=0x0
   .word 0x9B00   // code r/exec
   .word 0x00CF   // granuality 4096(4k)
   
    // data entry
   .word 0xFFFF   // limit=0xFFFFF=4GB
   .word 0x0000   // base=0x0
   .word 0x9300   // data r/w
   .word 0x00CF   // granularity 4096(4k)
gdt_boot_end:

// GDTR Pointer
gdtr_boot:
   .word gdt_boot_end - gdt_boot  // limit(16 bits)
   .long 0x0  // base address(32 bits)

   
setup_end:
.org 2044      // 4 sectors
   .ascii "ANAS"
.end
