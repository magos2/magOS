/* this is a High half kernel: kernel space start at 3GiB. userspace is located at 0-3GiB.
 * Bootloader loads kernel at LMA(Load address), specified by AT keyword(around 1MiB).
 * Virtual memory addresses(VMA) start at 0xc0100000.
 */
PAGE_OFFSET = 0xC0000000;
OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

SECTIONS
{
  . = 0xC0000000 + 0x100000;
  
  _stext = .;
  .text ALIGN(0x1000) : AT(ADDR(.text) - PAGE_OFFSET){
     *(.multiboot);  
     *(.text);
   }
   
   _etext = .; /*end of section .text*/
   
   .data ALIGN(0x1000) : AT(ADDR(.data) - PAGE_OFFSET){
      *(.data);
      *(__ksymtab);
   }
   
   _edata = .; /*end of section .data*/
   
   .bss ALIGN(0x1000) : AT(ADDR(.bss) - PAGE_OFFSET){
      _sbss = .;
      *(.bss);
      _ebss = .;
   }

   _end = .; /*end of kernel code/data*/
   
   /DISCARD/ : {
        *(.comment)
        *(.eh_frame)
        *(.note.gnu.build-id)
    }
}
