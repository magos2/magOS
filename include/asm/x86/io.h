#ifndef _ASM_IO_H
#define _ASM_IO_H

#define outb(value,port) \
	__asm__("outb %%al, %%dx"::"a"(value), "d"(port))

/* outb avec pause*/
#define outb_p(value,port) \
   __asm__("outb %%al, %%dx \n\t" \
           "jmp 1f \n\t" \
	        "1:"::"a"(value), "d"(port))
	

#define inb(port) \
  ({ unsigned char _value;\
	 __asm__ volatile("inb %%dx, %%al":"=a"(_value):"d"(port));\
	 _value; })

#define inb_p(port) \
   ({ unsigned char _value;\
	  __asm__ volatile("inb %%dx, %%al \n\t" \
	                    "jmp 1f \n\t" \
	                    "1:":"=a"(_value):"d"(port));\
	  _value; }) 	
	
	
#endif 
