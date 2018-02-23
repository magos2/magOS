#ifndef _PTRACE_H
#define _PTRACE_H

/*this gives a photo how registers ar stored on the stack 
 *following a system call. this is hard-coded, dont touch if you dont
 *know wath do you do. see  sys_call.S.
 */
#define _EBX  0
#define _ECX  4
#define _EDX  8
#define _ESI  12
#define _EDI  16
#define _EBP  20
#define _EAX  24
#define _ES   28
#define _DS   32
#define _ERROR_CODE   36
#define _EIP  40
#define _CS   44
#define _EFLAGS  48
#define _ESP     52
#define _SS      56

/*this struct describe how cpu context is saved on stack when
 *an interrupt occurs.
 *selectors(cs,ds,etc) are 16-bit long. high 16-bit are unused.
 */
struct pt_regs {
  unsigned long ebx;
  unsigned long ecx;
  unsigned long edx;
  unsigned long esi;
  unsigned long edi;
  unsigned long ebp;
  unsigned long eax;
  unsigned long xes; /*x:16 high bits are unused*/
  unsigned long xds;
  unsigned long error_code;
  unsigned long eip;
  unsigned long xcs;
  unsigned long eflags;
  unsigned long esp;
  unsigned long xss;
};

void show_registers(struct pt_regs *regs);
void show_stack(struct pt_regs *regs);
void show_trace(struct pt_regs *regs);

#endif