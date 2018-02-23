/*_ Copyright 2016 @AR
 *
 * kmalloc : kernel heap allocator
 *
 * very simple kmalloc, using a pseudo buddy algorithm.
 * a page frame is divided into blocks with same size/order.
 */
#include <types.h>
#include <errno.h>
#include <mm.h>
#include <kernel.h>    
#include <list.h>

#define KMALLOC_MIN_SIZE  4  //bytes
#define KMALLOC_MAX_SIZE  (PAGE_SIZE - sizeof(struct chunk_head)) 

#define next_chunk(chunk)  ((struct chunk_head*)((unsigned long)chunk + sizeof(struct chunk_head) + chunk->size))
#define real_size(chunk)   (chunk->size + sizeof(struct chunk_head))
#define is_free(chunk)    (chunk->inuse == 0)

#define MAX_ORDER 7
#define DEBUG 0

/*block head. this is in frnt of evry block, free or used*/
struct block_head {
  int flags;
  struct block_head *next;
};
typedef struct block_head block_head_t;

/*a page is splitted into same size blocks.
  page desc is in front of any page of the heap.
 */
struct page_desc {
  struct page_desc *next;
  block_head_t *firstfree;
  int order;
  int nfrees; /*free blocks*/
};
typedef struct page_desc page_desc_t;

struct size_desc {
  int blocksize; /*in bytes*/
  int nblocks; /*how many blocks per page*/
  page_desc_t *firstfree;
  int nmallocs;
  int nfrees; /*nb of free blocks*/
  int npages;
};

struct size_desc sizes[MAX_ORDER+1] = 
                        {{32,   102, NULL, 0, 0, 0},
                         {64,   56, NULL, 0, 0, 0},  
                         {128,  30, NULL, 0, 0, 0},
                         {256,  15, NULL, 0, 0, 0},
                         {512,  7, NULL, 0, 0, 0},
                         {1012, 4, NULL, 0, 0, 0},
                         {2032, 2, NULL, 0, 0, 0},
                         {4072, 1, NULL, 0, 0, 0}};
                

int get_order(size_t size) 
{
  int i;
  for (i=0; i<=MAX_ORDER; i++)
    if (sizes[i].blocksize >= size)
      return i;
  return -EAGAIN;
}
/* augmenter le heap de n pages, associer a order
   nblocks = sizes[order].nblocks
   a1: allouer une page
       map the page
   a2: create page_desc on front of page
   a3: create the nblocks headers
   a4: n=n-1, if n>0 goto a1 
 */
int ksbrk (int n, int order, int flags)
{
  int i;
  page_desc_t *page, *ptmp;
  block_head_t *bh, *tmp;
  int nblocks, blocksize;
  
  nblocks = sizes[order].nblocks;
  blocksize = sizes[order].blocksize;
  page = (page_desc_t *)get_free_page(flags);
  if (!page)
    return -ENOMEM;
  page->order = order;
  page->nfrees = nblocks;
  bh = (block_head_t *)((unsigned long)page + sizeof(page_desc_t));
  page->firstfree = bh;
  for (i=1; i < nblocks; i++) {
    tmp = (block_head_t *)((unsigned long)bh + sizeof(block_head_t) + blocksize);
    bh->next = tmp;
    bh = tmp;
  }
  bh->next = NULL;
  ptmp = sizes[order].firstfree;
  sizes[order].firstfree = page;
  page->next = ptmp;
  sizes[order].nfrees += nblocks;
  sizes[order].npages++;
  return 0;
}

/* kmalloc algo: allouer size bytes
   order = ORDER(size)
   ret
   a0:sanity checks
     - max size <= sizes[0].size
   a1: si firstfree page est vide , ksbrk
   a2: prendre le firstfree head de la firstfree page
       ret = firstfree_head + sizeof(bh)
       firstfree_page.firstfree = firstfree_head.next
       firstfree_page.nfree--
   a3: si firstfree_page.nfree == 0, sizes[order].firstfree=firstfree.next
 */ 
void * kmalloc (size_t size, int flags) 
{
  int err;
  int order, nfrees;
  page_desc_t *page;
  block_head_t *bh;
  unsigned long addr;
  
  /*sanity checks*/
  if (size > sizes[MAX_ORDER].blocksize) {
    printk ("kmalloc limit error, %dB wanted, but max permitted %dB\n", size, 
               sizes[MAX_ORDER].blocksize);
    return NULL;
  }  
  order = get_order(size);
  nfrees = sizes[order].nfrees;
  if (!nfrees) {
    if ((err=ksbrk(1, order, flags))) {
      panic ("cannot extend heap <%d>: out of memory", err);
      return NULL;
    }
  }
  page = sizes[order].firstfree;
  bh = page->firstfree;
  addr = (unsigned long)bh + sizeof(block_head_t);
  page->firstfree = bh->next;
  bh->flags = flags;
  bh->next = NULL;
  page->nfrees--;
  sizes[order].nfrees--;
  if (page->nfrees == 0)
    sizes[order].firstfree = page->next;
  return (void *)addr;
}                         

/* kfree free block at addr
   a1: trouver le block header
       bh = addr - sizeof(block_head)
   a2: trouver la page du block
       page = addr & PAGE_MASK
       order = page.order
   a3: mettre bh comme firstfree of the page 
       page.firstfree = bh
       bh->next = old page.firstfree
   a5: page.nfrees += 1     
   a6: si tous les blocks sont libres, liberer la page
         end_mehod
       sinon sizes[order].nfrees += 1  
   a4: si page.nfrees == 1,  il faut l ajouter dans sizes
         sizes[order].firstfree = page
         page->next = old sizes[order].firstfree 
 */
void kfree (void *addr) {
  int order;
  page_desc_t *page, *ptmp;
  block_head_t *bh, *tmp;
  
  bh = (block_head_t *)((unsigned long)addr - sizeof(block_head_t));
  page = (page_desc_t *)((unsigned long)addr & PAGE_MASK);
  order = page->order;
  tmp = page->firstfree;
  page->firstfree = bh;
  bh->next = tmp;
  page->nfrees++;
  sizes[order].nfrees++;
  if (page->nfrees == sizes[order].nblocks) { //page becomes comletly free
    sizes[order].firstfree = page->next;
    free_page((unsigned long)page);
    //unmap_page((unsigned long)page);
    sizes[order].npages--;
    sizes[order].nfrees -= sizes[order].nblocks;
    return;
  }
  if (page->nfrees == 1) { //bring page back to freelist
    ptmp = sizes[order].firstfree;
    sizes[order].firstfree = page;
    page->next = ptmp;
  }
}

void show_kheap ()
{
  int order, free_mem, used_mem, total_mem;
  page_desc_t *page;
  block_head_t *bh;
  
  free_mem=used_mem=total_mem=0;
  for (order=0; order <= MAX_ORDER; order++) {
    printk("Order %d, blocksise=%d, nblocks=%d, nfrees=%d, npages=%d :\n", order,
                   sizes[order].blocksize, sizes[order].nblocks,sizes[order].nfrees,sizes[order].npages);
    page = sizes[order].firstfree;
    while (page) {
      printk("  page %x : next=%x, nfrees=%d, order=%d, blocks=", (int)page, (int)page->next, page->nfrees, page->order);
      bh = page->firstfree;
      while(bh) {
        printk("%x-", (int)bh);
        bh = bh->next;
      }
      printk("\n");
      page = page->next;
    }
    total_mem += sizes[order].npages*PAGE_SIZE;
    free_mem += sizes[order].nfrees*sizes[order].blocksize;
  }
  used_mem = total_mem - free_mem;
  printk("kheap total:%d B free:%d B used:%d B\n\n", total_mem, free_mem, used_mem);
}

