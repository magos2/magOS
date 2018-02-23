#include <stdio.h>
//#include <stdlib.h>
#include <assert.h>
#include "list.h"

   

void test_list_add()
{
   LIST_HEAD(s_head1) ;
   LIST_HEAD(s_l2) ;
   LIST_HEAD(s_l3) ;
   LIST_HEAD(s_new) ;
   struct list_head *head1 = &s_head1;
   struct list_head *l2 = &s_l2;
   struct list_head *l3 = &s_l3;
   struct list_head *new = &s_new;

   
   printf("Testing list_add...\n");   
   list_add(l3, head1);
   list_add(l2, head1);
   list_add(new, head1);
   printf("head1=%p, head1->next=%p, head1->prev=%p\n", head1 , head1->next, head1->prev); 
   printf("l2=%p, l2->next=%p, l2->prev=%p\n", l2 , l2->next, l2->prev); 
   printf("l3=%p, l3->next=%p, l3->prev=%p\n", l3 , l3->next, l3->prev); 
   printf("new=%p, new->next=%p, new->prev=%p\n", new , new->next, new->prev); 
   assert(head1->next == new);
   assert(new->next == l2);
   assert(new->prev == head1);
   assert(l2->prev == new);
   assert(l2->next == l3);
   assert(l3->next == head1);
   assert(l3->prev == l2);
   printf("OK\n");   
}

void test_list_add_tail()
{
   LIST_HEAD(s_head1) ;
   LIST_HEAD(s_l2) ;
   LIST_HEAD(s_l3) ;
   LIST_HEAD(s_new) ;
   struct list_head *head1 = &s_head1;
   struct list_head *l2 = &s_l2;
   struct list_head *l3 = &s_l3;
   struct list_head *new = &s_new;

   printf("Testing list_add_tail...\n");   
   list_add_tail(l2, head1);
   list_add_tail(l3, head1);
   list_add_tail(new, head1);
   
   printf("head1=%p, head1->next=%p, head1->prev=%p\n", head1 , head1->next, head1->prev); 
   printf("l2=%p, l2->next=%p, l2->prev=%p\n", l2 , l2->next, l2->prev); 
   printf("l3=%p, l3->next=%p, l3->prev=%p\n", l3 , l3->next, l3->prev); 
   printf("new=%p, new->next=%p, new->prev=%p\n", new , new->next, new->prev); 
  
   assert(head1->prev == new);
   assert(new->next == head1);
   assert(new->prev == l3);
   assert(l3->next == new);
   assert(l3->prev == l2);
   assert(l2->next == l3);
   assert(l2->prev == head1);
   printf("OK\n");   
   
}

void test_list_del()
{
   LIST_HEAD(s_head1) ;
   LIST_HEAD(s_l2) ;
   LIST_HEAD(s_l3) ;
   struct list_head *head1 = &s_head1;
   struct list_head *l2 = &s_l2;
   struct list_head *l3 = &s_l3;
   
   printf("Testing list_del...");   
   list_add(l2, head1);
   list_add(l3, head1);
   
   list_del(l2);
   assert(head1->next == l3);
   assert(head1->prev == l3);
   assert(l3->prev == head1);
   assert(l3->next == head1);
   list_del(l3);
   assert(l3->next == NULL);
   assert(l3->prev == NULL);
   assert(head1->next == head1);
   assert(head1->prev == head1);

   printf("OK\n");   
   
}

void test_list_entry()
{

   printf("Testing test_list_entry...\n");   
   
   struct todo_struct {
      char *wath;
      struct list_head todo_list;
   };

   struct list_head *cursor;
   LIST_HEAD(s_todos);
   struct list_head *todos = &s_todos;

   struct todo_struct todo_1;
   struct todo_struct todo_2;
   todo_1.wath="mytodo1";
   todo_2.wath="mytodo2";
   
   list_add_tail(&(todo_1.todo_list),todos);
   list_add_tail(&(todo_2.todo_list),todos);

   list_for_each(cursor, todos) {
      struct todo_struct *todo = list_entry(cursor, struct todo_struct, todo_list); 
      printf("todo=<%s>\n", todo->wath); 
   }

   printf("[OK]\n");   

}
int main(int argv, char **args)
{
   test_list_add();
   
   test_list_add_tail();

   test_list_entry();

   test_list_del();
   
   return 0;
}

