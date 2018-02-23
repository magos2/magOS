/*
 * Copyrigth 2016 @AR
 * 
 * definit les procedures schedule() et switch_to()
 *
*/
#define KERNEL_DEBUG 0
#include <sched.h>
#include <segment.h>
#include <system.h>
#include <libc.h>
#include <bitops.h>
#include <errno.h>
#include <kernel.h>
#include <unistd.h>

extern tss_t default_tss;
extern void init_task();
extern void vmm_init(task_t *tsk);
extern void cpu_idle(void);
extern void do_switch(unsigned long esp, struct pt_regs*);
extern void ret_from_switch();
extern void ret_from_fork();

struct list_head tasks;
runqueue_t runqueue; 
pid_t last_pid = 0;
char init_stack[PAGE_SIZE];

#define INIT_TSS  {                                            \
              .ss0=KERNEL_DS,                                  \
              .ss=KERNEL_DS,                                   \
              .esp0=(unsigned long)&init_stack + PAGE_SIZE-16, \
              .esp=(unsigned long)&init_stack + PAGE_SIZE-16,  \
              .cr3=0,0                                         \
            }        
#define INIT_MM  {                          \
             .mmap=NULL, .map_count=0,      \
             .pgdir=(pde_t*)&swapper_pg_dir,\
             0,0,0,0, /*code, data*/        \
             0,0,0,0, /*heap,stack*/        \
             0,0,0,0  /*arg, env*/          \
            }   
#define INIT_REGS {                                                  \
              .xcs=KERNEL_CS,                                        \
              .xds=KERNEL_DS,                                        \
              .xes=KERNEL_DS,                                        \
              .xss=KERNEL_DS,                                        \
              .esp=(unsigned long)&init_stack+PAGE_SIZE-16,          \
              .eip=(u32)&cpu_idle                                    \
              }
/*process #0, cpu_idle*/
task_t INIT_TASK =
  {.pid=0, .state=TASK_RUNNABLE, 
  .prio=MAX_PRIO, 
  .parent=&INIT_TASK,                        
  .exit_code=0,                        
  .uid=0,.gid=0,                        
  .start_time=0,                        
  .counter=DEFAULT_TIMESLICE, .need_resched=0, 
  .stime=0, .utime=0,  
  .list={NULL,},                 
  .run_list={NULL,},                     
  .mm=INIT_MM,                         
  .tty=0, /*console 0*/                            
  .tss=INIT_TSS,
  .regs=INIT_REGS};                  

void switch_to(task_t *tsk)
{
  current = tsk;
  
  /* charger le default_tss avec la pile noyau du process */  
  default_tss.ss0 = tsk->tss.ss0; 
  default_tss.esp0 = tsk->tss.esp0;
  
  /*switch to tsk address space*/
  unsigned long cr3 = _pa((unsigned long)tsk->mm.pgdir);
  __asm__ volatile ("mov %%eax, %%cr3"::"a"(cr3):);
  
  asm ("mov %0, %%esp"::"m"(tsk->tss.esp):);/*switch stack ptr*/
  if (tsk->tss.eip == (unsigned long)&ret_from_fork)
    ret_from_fork();
  asm ("pushl %0"::"m"(tsk->tss.ebx):);
  asm ("pushl %0"::"m"(tsk->tss.edi):);
  asm ("pushl %0"::"m"(tsk->tss.esi):);
  ret_from_switch();
}

/* Algo
 *! schedule is always called in kernel mode !
 * return: to the instruction next to "call schedule"
 irq0 in usermode:
   esp=esp0 of current
   save_all (current context)
   do_timer:
     schedule:
       push ebp
       mov esp, ebp
       save current context(before sched):
         prev->resume_eip=ret_from_switch
         prev->resume_esp=ebp frame
         save ebx esi edi #GCC requires that these do not change accros function call
       prev=current
       next=to be elected
       switch_to (prev,next):
         current=next
         esp = switch to next esp
         test if ret_from_fork 
         push next.regs.ebx edi esi
         ret_from_switch()
 */
void schedule()
{   
  task_t *prev, *next;
  
  cli();
  prev = current;
  
  /* only idle process is running */
  if ( runqueue.nr_running <= 1) {
    current->counter = DEFAULT_TIMESLICE;
    current->need_resched = FALSE;
    return;
  }
  
  asm ("movl %%ebp, %0":"=r"(prev->tss.esp)::); /*save current kernel stack pointer. this is the entry point 
                                                  to be able to reschedule this current task*/                                                                                                                                                
  
  asm ("movl %%ebx, %0":"=r"(prev->tss.ebx)::); /*GCC requires that these registers do not change accros function call.*/
  asm ("movl %%edi, %0":"=r"(prev->tss.edi)::);
  asm ("movl %%esi, %0":"=r"(prev->tss.esi)::);
  
  prev->tss.eip = (unsigned long)&ret_from_switch;
  /* elect a task to resume */
  if (prev->state == TASK_RUNNABLE) 
    runqueue_move_end(prev);
  else if (prev->state == TASK_STOPPED) {
    runqueue_del (prev);
    list_del (&prev->list);
    pgdir_free(prev->mm.pgdir);
    free_page(prev->tss.esp0); 
    free_page((unsigned long)prev);
    debug ("process <%d> has been stopped!\n", prev->pid);
  }
  else if (prev->state == TASK_INTERRUPTIBLE) /*prev go to sleeping*/
    runqueue_del(prev);
  else
    panic("task state %d not supported!", prev->state);
  next = runqueue_first_task();

  next->counter = DEFAULT_TIMESLICE;
  next->need_resched = FALSE;

  /*switch to the elected task*/
  switch_to(next);
}

void reschedule() 
{}

void runqueue_init(void)
{
  runqueue.nr_running = 0;
  INIT_LIST_HEAD (&runqueue.queue);
  runqueue_add(&INIT_TASK);
  last_pid = 0; 
  current = idle = &INIT_TASK;
  
}
  
void sched_init ()
{
  INIT_LIST_HEAD (&tasks);
  list_add_tail(&INIT_TASK.list, &tasks);
  runqueue_init ();
  info ("Scheduler initialized.");
}


/* cree une task kernel qui va executer la routine pfn(pointer of function)
 * pfn and arg1 must be passed in registers because child chhange stack.
 */
int kernel_thread(register fn_ptr pfn, register void* arg1)
{
  pid_t pid;
  
  pid = fork();
  if (pid == 0) {  //child
    pfn (arg1);
    //exit(); TODO
  }
  // parent go here
  debug ("Creation of kernel thread pid %d. Ok\n", pid); 
  return pid; 
}

task_t *find_task (pid_t pid)
{
  struct list_head *p;
  task_t *tsk;
  list_for_each (p, &tasks) {
    tsk = list_entry(p, task_t, list);
    if (tsk->pid == pid)
      return tsk;
  }
  return NULL;
}

static char *state2str(int state)
{
  switch(state) {
  case        TASK_RUNNABLE: return "R";
  case   TASK_INTERRUPTIBLE: return "S";
  case TASK_UNINTERRUPTIBLE: return "S";
  case          TASK_ZOMBIE: return "Z";
  case         TASK_STOPPED: return "STOPPED!";
  }
  return "UNKNOWN";
}

int do_ps()
{
  struct list_head *cursor;
  task_t *tsk;
  printk("%10s%10s%10s%10s%10s\n","UID", "PID", "PPID", "State", "CMD");
  list_for_each (cursor, &tasks) {
    tsk = list_entry(cursor, task_t, list);
    printk("%10d%10d%10d%10s%10s\n", 
            tsk->uid,tsk->pid,tsk->parent->pid,
            state2str(tsk->state), "TODO");
  }
  return 0;
}
	
	
	
	
	
	
	







