/*
 * Copyright 2016 @AR
 *
 * this program define the timer(PIT 8253 - Programmable Interrupt Timer) isr
 * see: http://www.cs.dartmouth.edu/~spl/Academic/Organization/docs/PC%20Timer%208253.html
*/
#include <timex.h>
#include <io.h>
#include <sched.h>
#include <types.h>
#include <ptrace.h>

#define HZ                  100  /*frequence out. an interrupt every 10ms*/
#define CLOCK_TICK_RATE 1193180  /*frequence in. 1.19318Mz*/

#define LATCH (CLOCK_TICK_RATE / HZ) /* LATCH=11931.8 define the frequency divider*/   
                                                 


#define CHANNEL_0     0x40  /*counter 0 port*/
#define CHANNEL_1     0x41  /*counter 1 port*/
#define CHANNEL_2     0x42  /*counter 2 port*/
#define CTRL_PORT     0x43  /*Mode control port*/

unsigned long jiffies = 0;

void timer_handler(unsigned long esp)
{
  struct pt_regs *regs = (struct pt_regs *)esp;
  
  jiffies++;
  if (regs->xcs & 0x3)
    current->utime++;
  else
    current->stime++;
  
  /* s'il reste du timeslice, le current continue de s'executer */
  if (--(current->counter) > 0) {
    return;
  }
  schedule();
}

void _8253_init(void)
{
  outb_p(0b00110110, CTRL_PORT); /* binary, mode 3, LSB/MSB, ch 0*/ 
  outb_p(LATCH & 0xff, CHANNEL_0); /* LSB */
  outb_p(LATCH >> 8, CHANNEL_0);   /* MSB */
}



