
#include <stdio.h>
#include <stdlib.h>
#include <list.h>


struct bloc_head {
  int size;
  struct list_head list;
};

struct list_head freelist; /*list of free blocs.*/

char* mem; /*memory*/

void alloc_init()
{
  struct bloc_head *bh;
  
  INIT_LIST_HEAD(&freelist);
  
  mem = (char*) malloc(1024);
  bh = (struct bloc_head*)mem;
  bh->size = 1024;
  list_add (&bh->list, &freelist);
}

/* Algorithm: alloc(n)
A0. p = freelist
A1. 
    si p->size >= n, aller a A3
    sinon
      p = p->link
      si p == freelist aller a A2
      revenir a A1
A2. bloc non trouvé, error
A3. bloc trouvé
    - reduire la taille du bloc, et sa location.
    - si p->size == n, supprimer le bloc de freelist
*/
void* alloc (int n)
{
  struct bloc_head * bh = NULL, * new_bloc;
  struct list_head * p;
  
  list_for_each(p, &freelist) { 
    bh = list_entry (p, struct bloc_head, list);
    if (bh->size >= n)
      break;
  }
  
  // bloc non trouve
  if (!bh || bh->size < n) {
      printf("oom , cannot allocate %d bytes\n", n);
      return NULL;
  }
  
  // bloc trouve
  printf("allocate %d Bytes: free bloc of %d bytes found at %p\n",n , bh->size, bh);
  list_del(&bh->list);
  if (bh->size > n) { 
    new_bloc = (struct bloc_head*)((char*)bh + n);
    new_bloc->size = bh->size - n;
    list_add_tail(&new_bloc->list, &freelist);
  }
  return bh;
}

void show_freelist()
{
  struct list_head * p;
  struct bloc_head * bh;
  
  printf("freelist(addr,size,next,prev) : ");
  list_for_each(p, &freelist){
    bh = list_entry (p, struct bloc_head, list);
    printf ("--[%p, %d, %p, %p]--", bh, bh->size, p->next, p->prev);
  }
  printf("\n");
}

int main (void)
{
  alloc_init();
  show_freelist();
  
  alloc (128);
  alloc (384);
  show_freelist();
  
  alloc (512);
  show_freelist();
  
  alloc (4);
  
  return 0;
}







    