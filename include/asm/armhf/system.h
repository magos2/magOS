#ifndef _ASM_SYSTEM_H
#define _ASM_SYSTEM_H

#include "segment.h"

#define cli() __asm__ __volatile__("":::)
#define sti() __asm__ __volatile__("":::)
#define nop() __asm__ __volatile__("nop":::)
#define iret() __asm__ __volatile__("iret":::)

static inline __attribute__((always_inline)) void move_to_user_mode() 		   
{
__asm__(                            
      "movw %0, %%ax   \n\t"        
      "movw %%ax, %%ds \n\t"        
      "movw %%ax, %%es \n\t"        
      "movw %%ax, %%fs \n\t"        
      "movw %%ax, %%gs \n\t"        
      "pushl %0  \n\t"              
      "push %2    \n\t"            
      "pushf      \n\t"            
      "popl %%eax  \n\t"            
      "orl $0x200, %%eax       \n\t"
      "andl $0xffffbfff, %%eax \n\t"
      "push %%eax     \n\t"        
      "push %1        \n\t"        
      "push $0x100000 \n\t"        
      "iret"                        
      ::"i"(USER_DS), "i"(USER_CS), "i"(USER_STACK));			   
}				   
				
#define invalidate() __asm__("")    
				   
#define zero_mem(addr,nbytes) __asm__("")

static inline __attribute((always_inline)) 
void do_switch()
{}

static inline __attribute((always_inline))
unsigned long * get_switch_ebp()
{
  return (unsigned long*)0;
}



#endif
