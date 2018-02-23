#include <sched.h>
#include <errno.h>
#include <kernel.h>
#include <unistd.h>

void notify_parent()
{
  task_t *tsk = current->parent;
  if (tsk->state == TASK_INTERRUPTIBLE) {
    tsk->state = TASK_RUNNABLE;
    runqueue_add(tsk);
  }
}

/* terminate "immediatly" the cating process: 
 *   - close open file descriptors
 *   - if the parent is waiting, it is notified
 *   - destroys the process address space(done by scheduler)
 */
void do_exit ()
{
  if (current->pid == 0) {
    printk("cannot kill process 0 !\n");
    return;
  }
  notify_parent();
  current->state = TASK_STOPPED;
  schedule ();
}









