#include <ptrace.h>
#include <kernel.h>
#include <sched.h>

extern unsigned long _stext, _etext;

/*kallsyms.c*/
extern void ksym_lookup(unsigned long addr, char* buf);

void show_registers(struct pt_regs *regs)
{
  unsigned long cr0, cr2, cr3;
  
  printk("eip: %2x:%8x\n", regs->xcs, regs->eip);
  printk("eflags: %8x\n", regs->eflags);
  printk("eax: %8x  ebx: %8x  ecx: %8x  edx: %8x\n", regs->eax, regs->ebx, regs->ecx, regs->edx);
  printk("esi: %8x  edi: %8x  ebp: %8x  esp: %8x\n", regs->esi, regs->edi, regs->ebp, regs->esp);
  printk("cs: %2x  ds: %2x  es: %2x  ss: %2x\n", regs->xcs, regs->xds, regs->xes, regs->xss);
  asm ("mov %%cr0, %0":"=r"(cr0)::);  
  asm ("mov %%cr2, %0":"=r"(cr2)::);
  asm ("mov %%cr3, %0":"=r"(cr3)::);
  printk("cr0: %8x cr2: %8x  cr3: %8x\n",cr0, cr2, cr3);
  printk("Process (pid: %d  task: %8x)\n", current->pid, (unsigned long)current); 
}

void show_stack(struct pt_regs *regs)
{
  int i;
  int print_stack_depth = 24;
  unsigned long esp = (unsigned long)regs;
  
  printk("Stack: ");
  for (i=0; i < print_stack_depth; i++) {
    printk("%8x ", *((unsigned long*)esp + i));
    if((i+1)%8 == 0 && (i+1) < print_stack_depth)
      printk("\n       ");
  }
  printk("\n");
}

void show_trace(struct pt_regs *regs)
{
  unsigned long eip, ebp;
  char buf[128];
  int call_depth = 5;
  
  printk("Call trace:\n");
  eip = regs->eip;
  ebp = regs->ebp;
  ksym_lookup(eip, &buf[0]);
  printk("\t[<%8x>]  %s\n", eip, &buf[0]);
  /* stack in convention call. "push ebp; mov esp, ebp"
     |.....   |
     ---------- ebp
     |ebp     |
     ----------
     |eip     |
     ----------
     |...     |  ? stack
     ---------- 
  */
  while (ebp && call_depth--) {
    eip = *((unsigned long *)ebp + 1);
    ebp = *(unsigned long *)ebp;
    if (eip >= (unsigned long)&_stext && eip < (unsigned long)&_etext) {//to be sur!
      ksym_lookup(eip, &buf[0]);
      printk("\t[<%8x>]  %s\n", eip, &buf[0]);
    }
  }
  /*Other Method : scan the stack searching a .text addresses, this may be calling routine*/
}



