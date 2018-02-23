/* panic is used essentialy in mm/fs to indicate a major problem.
 * see panic() macro in kernel.h
 */
#include <stdarg.h>
#include <kernel.h>
#include <console.h>
#include <ptrace.h>

void oops(struct pt_regs *regs, unsigned long esp)
{
  if ((regs->xcs & 0x3) == 0){ //kernel mode
    regs->esp = esp + sizeof(struct pt_regs) - 8;
    regs->xss = KERNEL_DS;
  }
  show_registers(regs);
  show_stack(regs);
  show_trace(regs);
}
