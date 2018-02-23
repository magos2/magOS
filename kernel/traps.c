/* Copyrigth 2015
**  
** traps.c handles hardware exceptions(division by 0, int 3,...)
** 
** A double fault occurs when a fault occurs when the CPU is running the handler for a fault.
**  In this case the CPU pauses the execution of the fault handler and jumps to 
**  the double fault handler. A double fault is usually the result of a bug in the kernel.
** Triple fault : when it occurs the cpu reset
*/

#include <types.h>
#include <idt.h>
#include <traps.h>
#include <kernel.h>
#include <sched.h>
#include <ptrace.h>

extern void  divide_error(void);
extern void  _debug(void);
extern void  int3(void);
extern void  overflow(void);
extern void  segment_not_present(void);
extern void  double_fault(void);
extern void  triple_fault(void);
extern void  invalide_tss(void);
extern void  segment_not_present(void);
extern void  stack_segment_fault(void);
extern void  gpf(void);
extern void  page_fault(void);
extern void reserved(void);
extern void isr_default(void);

void die(char *msg, long esp, long error_code)
{
   struct pt_regs *regs = (struct pt_regs *)esp;
   printk("-- %s! --\n", msg);
   printk("esp=%x error_code=%x\n", esp, error_code);
   oops(regs, esp);
   panic(msg);
}

void do_divide_error(long esp, long error_code)
{
   die("Divide Error", esp, error_code);
}

void do__debug(long esp, long error_code)
{
   die("Debug", esp, error_code);
}

void do_int3(long esp, long error_code)
{
   die("Int3", esp, error_code);
}

void do_overflow(long esp, long error_code)
{
   die("Overflow", esp, error_code);
}

void do_double_fault(long esp, long error_code)
{
   die("double_fault", esp, error_code);
}

void do_triple_fault(long esp, long error_code)
{
   die("triple_fault", esp, error_code);
}

void do_invalide_tss(long esp, long error_code)
{
   die("invalide_tss", esp, error_code);
}

void do_segment_not_present(long esp, long error_code)
{
   die("segment not present", esp, error_code);
}

void do_stack_segment_fault(long esp, long error_code)
{
   die("stack seg fault", esp, error_code);
}

void do_gpf(long esp, long error_code)
{
  die("GPF General protection fault", esp, error_code);
}

void do_ignore(long esp, long error_code)
{
   die("Ignore error", esp, error_code);
}

void do_reserved(long esp, long error_code)
{
   die("Reserved trap 15, 17-31 error", esp, error_code);
}

void trap_init()
{
   int i;
   
   for (i=0; i<31; i++) {
      set_trap_gate(i,(long)&reserved);
   }
   set_trap_gate(0,(long)&divide_error);
   set_trap_gate(1,(long)&_debug);
   set_trap_gate(2,(long)&isr_default);
   set_trap_gate(3,(long)&int3);
   set_trap_gate(4,(long)&overflow);
   set_trap_gate(8,(long)&double_fault);
   set_trap_gate(10,(long)&invalide_tss);
   set_trap_gate(11,(long)&segment_not_present);
   set_trap_gate(12,(long)&stack_segment_fault);
   set_trap_gate(13,(long)&gpf);
   set_trap_gate(14,(long)&page_fault);
}
