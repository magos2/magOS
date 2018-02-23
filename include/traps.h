#ifndef _TRAPS_H
#define  _TRAPS_H
#include <ptrace.h>

void trap_init();

void show_registers(struct pt_regs *regs);
void show_stack(struct pt_regs *regs);
void show_trace(struct pt_regs *regs);

#endif
