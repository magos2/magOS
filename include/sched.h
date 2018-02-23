#ifndef _SCHED_H
#define _SCHED_H

#include <types.h>
#include <list.h>
#include <mm.h>
#include <file.h>
#include <ptrace.h>

#define TASK_RUNNABLE        0  /* process either running or on runqueue waiting to run  */
#define TASK_INTERRUPTIBLE   1  /* process sleeping */
#define TASK_UNINTERRUPTIBLE 2  /* idem */
#define TASK_ZOMBIE          3  /* process has terminated, but its parent has not yet issued a wait4.its desc remain in mem*/
#define TASK_STOPPED         4

#define MAX_PRIO   140
#define MAX_BITMAP (MAX_PRIO/32+1) 

#define MAX_OPEN 16  // max open files

#define mode_user(tsk)    ((tsk->regs.xcs & 0x3) == 0x3)
#define mode_kernel(tsk)  ((tsk->regs.xcs & 0x3) == 0)

#define MIN_TIMESLICE       3  
#define DEFAULT_TIMESLICE  20   /* 200ms */
#define MAX_TIMESLICE    3200

/*Task State Segment, only used to store kernel stack(esp0/ss0) of the current process.
 *other fields are unused, because we use soft switch instead of hard switch.
 */
struct tss_struct {
  u32 link;
  u32 esp0;
  u32 ss0; /* 16 high  bits zero */
  u32 esp1;
  u32 ss1; /* 16 high  bits zero */
  u32 esp2;
  u32 ss2; /* 16 high  bits zero */
  u32 cr3, eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
  u32 es; /* es,cs...gs : 16 high  bits zero */
  u32 cs; 
  u32 ss; 
  u32 ds;
  u32 fs;
  u32 gs;
  u32 ldt; /* 16 high  bits zero */
  u32 iopb; /* 16 low  bits zero */
} __attribute__((packed));

typedef struct tss_struct tss_t;

struct task_struct {
  pid_t pid;  
  long state;  /* -1 unrunnable, 0 runnable, >0 stopped */  
  long prio;
  struct task_struct *parent;
  int exit_code;
  unsigned long start_time;
  int counter;    /*define timesclice, if counter<0 then reschedule this task */  
  int need_resched; /*si need_resched=0, il reste du timeslice, le current continue de s'executer*/

  unsigned long stime, utime;
  
/*process credentials*/
  unsigned short uid;
  unsigned short gid;
  
/* linked list for all tasks */
  struct list_head list;
  
/* linked list for running tasks */
  struct list_head run_list;

/* linked list for waiting tasks */
  struct list_head wait_list;
  
/*memory management*/
  mm_t mm;
  
/* FS info */
  struct file * filp[MAX_OPEN];
  struct file *root;  /*root directory "/", inode 2 */
  struct file *pwd;   /*current directory*/

/*tty*/
  int tty; /* -1 if no tty, so it must be signed */

/* Task switch segment and regs */
  tss_t tss;   
  struct pt_regs regs;
};

typedef struct task_struct task_t;

/* chaque process dispose d'une pile noyau, d'une page de 4ko.
 * sur le bas de la pile est stocké la structure du process */
union task_union {
  task_t task;
  char kstack[PAGE_SIZE]; /* pile noyau */
};

/* chaque bit du bitmap represente une priorité. une prio est a 1 si elle a
 * queue de 1 ou plusieurs runnable tasks */
struct prio_array_struct {
  struct list_head queue[MAX_PRIO+1]; 
};

typedef struct prio_array_struct prio_array_t;

struct runqueue_struct {
  unsigned long nr_running; /* number of runnable tasks */
  task_t *current;          /* task running currently */
  task_t *idle;             /*pointes on INIT_TASK*/
  struct list_head queue;   /*running tasks queue
                              queue-->|INIT_TASK|-->|p1 |-->|p2 |*/
};

typedef struct runqueue_struct runqueue_t;

extern runqueue_t runqueue; 
#define current (runqueue.current)
#define idle (runqueue.idle)

#define runqueue_add(tsk)  do {                                                      \
                             list_add_tail(&(tsk)->run_list, &runqueue.queue);       \
                             runqueue.nr_running++;                                  \
                           } while(0)
                           
#define runqueue_del(tsk)  do {                                                 \
                             if (tsk == idle)                                   \
                               panic("process 0 cannot be removed from rq!\n"); \
                             list_del(&(tsk)->run_list);                        \
                             runqueue.nr_running--;                             \
                           } while(0)
                           
#define runqueue_move_end(tsk) do {                                                  \
                                 if (tsk != idle)                                    \
                                   list_add_tail(&(tsk)->run_list, &runqueue.queue); \
                               } while(0)
                               
#define runqueue_first_task()    ({task_t* tsk;                                               \
                                  if (runqueue.nr_running > 1)                              \
                                    tsk = list_entry(idle->run_list.next, task_t, run_list);\
                                  else                                                      \
                                    tsk = idle;                                             \
                                  tsk;})                                          
                                  
                               
       
void sched_init ();
void schedule();
void reschedule();
int kernel_thread(fn_ptr pfn, void* arg1);

int do_ps();
#endif