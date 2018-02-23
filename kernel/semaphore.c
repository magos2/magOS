/* @AR 2017
 *
 * Semaphres/Monitors implementation
 */
#include <semaphore.h>
#include <sched.h>

void sem_init (semaphore_t *sem, int val)
{
  sem->val = val;
  waitqueue_init (&sem->waitq);
}

void down (semaphore_t *sem)
{
  task_t *tsk;
  
  if (sem->val == 0) {
    tsk = current;
    wait_queue_entry_t wait = {tsk, {NULL,}};
    waitqueue_add (&wait, &sem->waitq);
    tsk->state = TASK_INTERRUPTIBLE;
    schedule();
    waitqueue_del(&wait);
  }
  else
    sem->val--;
}

void up (semaphore_t *sem)
{
  wait_queue_entry_t *wait;
  task_t *tsk;
  
  sem->val++;
  if (!list_empty(&sem->waitq)) {
    wait = list_entry(sem->waitq.next, wait_queue_entry_t, wait_list);
    tsk = wait->task;
    tsk->state = TASK_RUNNABLE;
    runqueue_add(tsk);
  }
}





















