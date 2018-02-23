#ifndef _ASM_SYSTEM_H
#define _ASM_SYSTEM_H

#include <segment.h>
#include <ptrace.h>
#include <sched.h>

#define cli() __asm__ __volatile__("cli":::)
#define sti() __asm__ __volatile__("sti":::)
#define nop() __asm__ __volatile__("nop":::)
#define iret() __asm__ __volatile__("iret":::)
#define halt() __asm__ __volatile__("hlt":::)

static inline __attribute__((always_inline)) 
void move_to_user_mode() 		   
{
  __asm__ volatile (
    "pushl %0 \t\n" /*ss*/
    "pushl %1 \t\n" /*esp*/
    "pushfl \t\n"
    "pop %%eax \t\n"
    "orl $0x200, %%eax \t\n" /*activating interrupts*/
    "andl $0xffffbfff, %%eax \n\t"
    "push %%eax \n\t" /*eflags*/
    "pushl %2 \t\n"  /*cs*/
    "pushl 1f \t\n"   /*eip*/
    "iret \t\n"
    "1: mov %0, %%ax \n\t"
    "   mov %%ax, %%ds \n\t"
    "   mov %%ax, %%es \n\t"
    ::"i"(USER_DS), "i"(USER_STACK), "i"(USER_CS):"eax");	 
}				   
				
#define invalidate() __asm__("movl %%cr3, %%eax\n\tmovl %%eax, %%cr3":::"eax")    

#define zero_mem(addr,nbytes)  \
              __asm__(                          \
                  "cld\n\t"                     \
                  "xor %%al, %%al\n\t"          \
                  "rep; stosb"                  \
                  ::"c"(nbytes),"D"(addr));

#endif
