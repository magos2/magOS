/* 
 * Copyright 2016 @AR
 *
 * Forking process.
  call do_fork
  cmp eax, 0
  jne 1f
  call execve
  1: parent 
    code suite
 */
#include <types.h>
#include <errno.h>
#include <bitops.h>
#include <segment.h>
#include <kernel.h>
#include <ptrace.h>
#include <mm.h>
#include <sched.h>

extern pid_t last_pid;
extern struct list_head tasks;
extern runqueue_t runqueue; 	
extern void vmm_init(task_t *tsk);
extern void ret_from_syscall(void);
extern void ret_from_fork();
extern int copy_page_tables (task_t *tsk);
extern void info_tlb(task_t *tsk);

int find_empty_process ()
{
  last_pid++;
  if (last_pid == -1)
    return -EAGAIN; //TODO
  return last_pid;
}

void dup_mmap ()
{
  
}

void copy_file_descriptors (task_t *tsk)
{
  int i;
  for (i = 0; i < MAX_OPEN; i++) 
    tsk->filp[i] = current->filp[i];
}

/* fork parent process, create a new process with new addressing space. All pages are COW(copy-on-write) , 
 * and shared with the two process until a page fault witch makes privates copies.
 * create a copy of the parent process, use execv() to replace parent binary by the child one.
 * Algo:
  - create address space : page dir. 1 page/4kB
  - allocate a page frame for kernel stack. 1page/4kB.
    each process has its own kernel stack.
  - child return 0, parent return child_pid
  int 80, fork:from usermode
    SAVE_ALL: on parent kstack
    push esp
    call do_fork:
      push eip
      push ebp
      mv esp, ebp
      parent:
        return pid
      child:
        
 */
pid_t do_fork(struct pt_regs *regs)
{
  pid_t child_pid;
  task_t *p;
  unsigned long kernel_stack_page = 0;
  
  child_pid = find_empty_process();
  if (child_pid < 0) {
    printk("too many process to fork the process id <%d>\n", current->pid);
    return -EAGAIN;
  }
  p = (struct task_struct *)__get_free_page(GFP_KERNEL);
  if (!p)
    goto bad_fork_cleanup;
  *p = *current;  /*copy the parent in child*/
  list_add_tail (&p->list, &tasks);
  p->pid = child_pid;
  p->prio = current->prio;
  p->state = TASK_UNINTERRUPTIBLE; //to ensure that it does not run yet
  p->counter = DEFAULT_TIMESLICE;
  p->need_resched = FALSE;
  p->stime = p->utime = 0;  
  p->parent = current;
  p->regs = *regs; /*copy the parent regs(before sys_fork) */
  p->regs.eax = 0; /*child rturn 0*/
  if (!(kernel_stack_page = __get_free_page(GFP_KERNEL)))
    goto bad_fork_cleanup;
  p->tss.esp0 = kernel_stack_page + PAGE_SIZE - 16;
  p->tss.ss0 = KERNEL_DS; 
  p->tss.esp = p->tss.esp0;
  p->tss.esp -= sizeof(struct pt_regs);
  *(struct pt_regs*)p->tss.esp = p->regs;
  p->tss.eip = (unsigned long)&ret_from_fork;
  INIT_LIST_HEAD(&(p->run_list));

  /* Page Directory */
  if (copy_page_tables(p) < 0)
    goto bad_fork_cleanup_pgd;
  copy_file_descriptors(p);
  /* task vm areas */
  last_pid = child_pid;
  p->state = TASK_RUNNABLE;
  runqueue_add(p);
  return child_pid; /*parent return child pid*/
  
bad_fork_cleanup:
  panic ("cannot fork the process %d : out of memory", current->pid);
  free_page((unsigned long)p);
  return -ENOMEM;
  
bad_fork_cleanup_pgd:
  panic ("cannot fork the process %d : out of memory", current->pid);
  pgdir_free(p->mm.pgdir);
  free_page(kernel_stack_page); 
  free_page((unsigned long)p);
  return -ENOMEM;
}












