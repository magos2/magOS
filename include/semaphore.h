#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H
#include <wait.h>

struct semaphore {
  int val;
  wait_queue_t waitq;
};

typedef struct semaphore semaphore_t;

void sem_init (semaphore_t *sem, int val);
void down (semaphore_t *sem);
void up (semaphore_t *sem);

#endif













