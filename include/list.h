#ifndef MAGOS_LIST_H
#define MAGOS_LIST_H
/*
 * Copyrigth 2016 @AR
 *
 * Linked lists, doublement chainées et circulaires
 *
*/
#include <types.h>
#include <stddef.h>

struct list_head {
   struct list_head *next, *prev;
};

typedef struct list_head list_head_t;

#define LIST_HEAD_INIT(name) {&(name), &(name)}

#define LIST_HEAD(name) \
   struct list_head name = LIST_HEAD_INIT(name);
 
#define INIT_LIST_HEAD(ptr)                     \
   do {                                         \
      (ptr)->next = (ptr); (ptr)->prev = (ptr); \
   } while(0)
      
#define list_entry(ptr, type, field_name) \
   (type *) ((char *)(ptr) - offsetof(type, field_name))   

#define list_for_each(cursor,head) \
   for (cursor=(head)->next; cursor!=(head); cursor=cursor->next)

#define list_empty(ptr)\
   ((ptr)->next ==  NULL || (ptr)->prev ==  NULL || (ptr)->next ==  (ptr) || (ptr)->prev ==  (ptr))   

/* insert new juste apres head, 
 * permet d'implementer stack LIFO(Last In Firt Out)
 */
static inline void list_add(list_head_t *new, list_head_t *head)
{
   head->next->prev = new;
   new->next = head->next;
   new->prev= head;
   head->next = new;
};

/* insert new juste avant head, donc a la fin. 
 * permet d'implementer des queues FIFO(First In Firt Out)
 */
static inline void list_add_tail(list_head_t *new, list_head_t *head)
{
   head->prev->next = new;
   new->next = head;
   new->prev = head->prev;
   head->prev = new;
};

/* supprime entry de sa liste */
static inline void list_del(list_head_t *entry)
{
   entry->prev->next = entry->next;
   entry->next->prev = entry->prev;
   entry->prev = entry->next = entry;
};


#endif
