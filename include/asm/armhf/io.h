#ifndef _ASM_IO_H
#define _ASM_IO_H

#define outb(value,port) \
	__asm__(""::)

/* outb avec pause*/
#define outb_p(value,port) __asm__("")
 
	

#define inb(port) \
  ({ unsigned char _value = 0;\
	 __asm__ volatile(""::);\
	 _value; })

#define inb_p(port) \
   ({ unsigned char _value = 0;\
	  __asm__ volatile("\n\t" \
	                    "\n\t" \
	                    "1:"::);\
	  _value; }) 	
	
	
#endif 
