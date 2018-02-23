#ifndef _WAIT_H
#define _WAIT_H
#include <list.h>
#include <sched.h>

typedef struct list_head wait_queue_t;

struct wait_queue_entry {
  task_t *task;
  list_head_t wait_list;
};
typedef struct wait_queue_entry wait_queue_entry_t;


inline static void waitqueue_init (wait_queue_t *waitq)
{
  INIT_LIST_HEAD(waitq);
};

inline static void waitqueue_add(wait_queue_entry_t *entry, wait_queue_t *waitq)
{                                  
  list_add_tail(&entry->wait_list, waitq);                            
};

inline static void waitqueue_del(wait_queue_entry_t *entry)
{  
  list_del(&entry->wait_list);           
};

void sleep();
int wakeup(task_t *tsk);
void do_wait();

#endif



