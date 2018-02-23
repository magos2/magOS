/* Allocation de pages de 4ko, 8ko,..., 2^9*4ko(=2Mo)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <list.h>

#define PAGE_SIZE  4096
#define PAGE_SHIFT 12
#define PAGE_MASK  0xfffff000

#define IS_FREE(page)  (((page)->count <= 0)?1:0)

#define MAX_ORDER  9

#define MAP_NR(addr) (((addr) - start_mem) >> PAGE_SHIFT)


/*physical page*/
struct page {
  int flags;     /*PG_dirty, PG_DMA, PG_LOCKED(cannot be swapped out)*/
  int count;     /*references on this page, page free if =0, used if >0*/
  void *virtual; /*page virtual address*/
  unsigned long addr;
  int order;
  struct list_head list; /*in page freelist*/
  struct list_head buffers;
};

char * mem; /*memory, to simulate real memory*/
struct page * mem_map; /*memory map*/
unsigned long start_mem;
unsigned long end_mem;

int num_phypages;

struct size_desc {
  int size;
  struct list_head freelist; 
};

struct size_desc buddy_sizes[MAX_ORDER+1] = 
                     {{1, {}},
                      {2, {}},
                      {4, {}},
                      {8, {}},
                      {16, {}},
                      {32, {}},
                      {64, {}},
                      {128, {}},
                      {256, {}},
                      {512, {}}};
                     
             
void mem_init()
{
  unsigned long addr;
  int pages_nr;
  
  mem = (char*) malloc(1024*1024*16); /*16Mo*/
  start_mem = (int)mem;
  end_mem = start_mem + 1024*1024*16 - 1;
  pages_nr = 1 + ((end_mem - start_mem) >> PAGE_SHIFT);
  mem_map = (struct page*)start_mem;
  start_mem += sizeof(struct page)*pages_nr;
  start_mem &= PAGE_MASK;
  start_mem += PAGE_SIZE;  //must be aligned on 4kB
  addr = start_mem;
  while (addr < end_mem) {
    mem_map[MAP_NR(addr)].addr = addr;
    mem_map[MAP_NR(addr)].order = 0;
    mem_map[MAP_NR(addr)].count = 0;
    addr += PAGE_SIZE;
    num_phypages++;
  }
}

void alloc_init()
{
  int i;
  unsigned long addr;
  struct page *pg;
  
  for (i=0; i<=MAX_ORDER; i++)
    INIT_LIST_HEAD(&buddy_sizes[i].freelist); 
  
  //au depart on met toutes les pages dans MAX_ORDER
  addr = start_mem;
  while (addr < end_mem) {
    pg = &mem_map[MAP_NR(addr)]; 
    pg->order = MAX_ORDER;
    pg->count = 0;
    list_add_tail(&pg->list, &buddy_sizes[MAX_ORDER].freelist);
    addr += buddy_sizes[MAX_ORDER].size * PAGE_SIZE;
  }
  
}

/* algorithm. input:order. output:pointer to allocated pages.
 * A1 : trouver j, avec [order<=j<=9], buddy_sizes[j].freelist non vide.
        si non trouve aller a A3
 * A.1.1 : p = buddy_sizes[j].freelist->next
           supprimer p de la freelist
 * A2 : [trouve] : spliter les blocs, les inserer dans freelist inferieurs jusqu'a j=order
 * A.2.1: si j == order, retourner LOC(p)       
 * A.2.2: sinon
          j = j - 1
          decouper p en deux blocs.
          LOC(new_p) = LOC(p) + 2^j
          inserer new_p dans buddy_sizes[j].freelist
          p->size = p->size/2     
          retourner a A.2.1
 * A3 : [non trouve] : afficher erreur OOM. et retourner NULL.
 */
unsigned long alloc_pages(int order)
{
  int j;
  unsigned long new_addr;
  struct list_head *p;
  struct page *pg, *new_pg;
  
  //sanity checks
  if (order < 0 || order > MAX_ORDER) {
    printf("we cannot allocate more %d order\n", MAX_ORDER);
    return 0;
  }
  
  for (j=order; j <= MAX_ORDER; j++)
    if (!list_empty(&buddy_sizes[j].freelist))
       break;
  if (j > MAX_ORDER) 
    goto oom_err;
  p = buddy_sizes[j].freelist.next;
  list_del(p);
  pg = list_entry(p, struct page, list);
  while (j > order) {
    j--;
    new_addr = pg->addr + (1<<j) * PAGE_SIZE;
    new_pg = &mem_map[MAP_NR(new_addr)];
    new_pg->order = j;
    new_pg->count = 0;
    list_add(&new_pg->list, &buddy_sizes[j].freelist);
  }
  pg->order = order;
  pg->count = 1;
  return pg->addr;
  
oom_err:
  printf("OOM, no free memory to allocate %d\n", order);
  return 0;
}

/* free allocated pages at <addr>
 * F.1 : trouver <page> dans mem_map
   F.1.1 : si <page> is already free, exit.
   F.2 : recuperer <order> avec lequel ces pages ont ete alloué
   F.3 : marquer comme free
   F.4 : si <page> a un buddy , noté <bud>, dans la freelist de <order>, 
          --- ie : buddy.addr == page.addr +/- 2^order*PAGE_SIZE
          - SIZE(page) = 2*SIZE(page)
          - supprimer <bud> de freelist
          - si <bud>.addr < page.addr
              page.addr = <bud>.addr
          - <order> = order + 1
          - retourner a F4
        sinon
          - inserer <page> dans freelist de <order>
 */
void free_pages (unsigned long addr)
{
  int j;
  struct page *page, *tmp, *bud;
  struct list_head  *p;
  
  page = &mem_map[MAP_NR(addr)];
  if (IS_FREE(page))
    return;
  j = page->order;
  do {
    bud = NULL;
    list_for_each (p, &buddy_sizes[j].freelist) {
      tmp = list_entry(p, struct page, list);
      if (tmp->addr == (page->addr + (1<<j)*PAGE_SIZE) || 
          tmp->addr == (page->addr - (1<<j)*PAGE_SIZE)) {
        bud = tmp;
        break;
      }
    }
    if (bud) {
      list_del(&bud->list);
      if (bud->addr < page->addr)
        page = bud;
      j++;
    }
  } while (bud && j < MAX_ORDER);
  page->order = j;
  page->count = 0;
  list_add(&page->list, &buddy_sizes[j].freelist);
}
	
	
void show_mem()
{
  struct list_head * p;
  struct page * pg;
  int i;
  
  printf ("nb of physical pages : %d\n", num_phypages);
  for (i=0; i <= MAX_ORDER; i++) {
    printf ("order (%d), ", i);
    printf("freelist: ");
    list_for_each(p, &buddy_sizes[i].freelist) {
      pg = list_entry (p, struct page, list);
      printf ("%lx-->", pg->addr);
    }
    printf("\n");
  }
  printf("\n");
}

int main (void)
{
  unsigned long addr, page1;
  
  mem_init();
  alloc_init();
  
  show_mem();
  
  page1 = alloc_pages (0);
  show_mem();
  free_pages(page1);
  show_mem();
  
  while (( addr=alloc_pages (9) ))
    printf ("allocate 9 order at %#lx\n", addr);
  
  return 0;
}










