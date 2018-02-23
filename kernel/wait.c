#define KERNEL_DEBUG 0
#include <wait.h>
#include <kernel.h>


/*
 * this method make sleeping the current task.
 * the task will waked up by one of its children[notify_parent when exit]
 */
void do_wait()
{
  task_t *tsk = current;
  debug("process <%d> is made waiting", tsk->pid);
  tsk->state = TASK_INTERRUPTIBLE;
  schedule();
}

/*sleep current task on a wait queue:
 * 1. move current from runqueue to waitqueue.
 * 2. schedule
 * 3. once task is awakened, move it to runqueue
 */
void sleep()
{
  task_t *tsk = current;
  debug("process <%d> is made sleeping", tsk->pid);
  tsk->state = TASK_INTERRUPTIBLE;
  schedule();
}

/*this takes a task off the waitqueue and puts it in the runqueue.
 *task state will be update, and task will be electible to run.
 */
int wakeup(task_t *tsk)
{
  debug("process <%d> is waked up", tsk->pid);
  if (tsk->state == TASK_INTERRUPTIBLE) {
    tsk->state = TASK_RUNNABLE;
    runqueue_add(tsk);
  }
  return 0;
}






