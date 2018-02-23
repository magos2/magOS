ENTRY(startup_32)
_KERNEL_BASE = 0x1000;
SECTIONS
{
  .text.start(_KERNEL_BASE):{
      ../bin/boot/head.o ( .text )    
   }

   .text : ALIGN(0x1000) {
      _TEXT_START = .;
         *(.text)
      _TEXT_END = .;

   }
   
   .data : ALIGN(0x1000) {
      _DATA_START = .;
         *(.data)
      _DATA_END = .;

   }
   
  .bss : ALIGN(0x1000) {
      _BSS_START = .;
         *(.bss)
      _BSS_END = .;

   }

}
