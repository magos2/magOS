/*
 * Copyright 2016 @AR
 *
 * Mamory Paging.
 * PGT : Page Table
 * PGD : Page Directory
 *
*/ 
#define KERNEL_DEBUG 0
#include <types.h>
#include <mm.h>
#include <page.h>
#include <pgtable.h>
#include <bitops.h>
#include <kernel.h>
#include <system.h>
#include <list.h>

page_t * mem_map;    /* table de toutes pages physiques*/
int   mem_map_len;
int   reserved_pages;/*les n premieres pages reserve*/

struct list_head free_dma_pages;
struct list_head free_normal_pages;
struct list_head free_high_pages;

/*Initilize phyical memory map (mem_map). that manipulate physical address, for this raison we
 * use PAGE_NR macro instead of MAP_NR.
 * start_mem : all pages from 0..start_mem are reserved(kernel boot code/data). 
 *             cannot be allocated neither freed dynamicaly.
 */
unsigned long mem_init(unsigned long start_mem, unsigned long end_mem)
{
   unsigned long addr;
   page_t *page;
   
   mem_map = (page_t *)start_mem;
   mem_map_len = 1 + PAGE_NR(end_mem); /*number of physical pages*/
   start_mem += (mem_map_len * sizeof(page_t));
   start_mem = PAGE_ALIGN(start_mem);
   reserved_pages = PAGE_NR(start_mem);
   INIT_LIST_HEAD(&free_dma_pages);
   INIT_LIST_HEAD(&free_normal_pages);
   INIT_LIST_HEAD(&free_high_pages);
   for (addr = 0; addr < START_LOW_MEM; addr += PAGE_SIZE) {
     page = &mem_map[PAGE_NR(addr)];
     page->addr = addr;
     page->count = 1;
     set_page_reserved(page);
     page->prot = 0;
     page->virt = 0;
   }
   for (addr = START_LOW_MEM; addr < start_mem; addr += PAGE_SIZE) {
     page = &mem_map[PAGE_NR(addr)];
     page->addr = addr;
     set_page_reserved(page);
     page->count = 1;
     page->prot = 0;
     page->virt = 0;
   }
   for (addr = start_mem; addr < end_mem; addr += PAGE_SIZE) {
     page = &mem_map[PAGE_NR(addr)];
     page->addr = addr;
     page->count = 0;
     page->flags = 0;
     page->prot = 0;
     page->virt = 0;
     if (addr < ZONE_NORMAL)
       list_add(&page->list, &free_dma_pages);
     else if (addr < ZONE_HIGHMEM)
       list_add(&page->list, &free_normal_pages);
     else
       list_add(&page->list, &free_normal_pages);//todo free_high_pages, see test
   }
   info ("Physical Memory Manager Initialized.");
   return start_mem;
}

void free_page(unsigned long addr)
{
  page_t * page;
  
  if (!addr)
    return;
  if (MAP_NR(addr) < reserved_pages)
    return;
  page = &mem_map[MAP_NR(addr)];
  //unmap_page(addr);
  page->virt = 0;
  page->count--;
  if (page->count == 0) {
    if (_pa(addr) < ZONE_NORMAL)
      list_add(&page->list, &free_dma_pages);
    else if (_pa(addr) < ZONE_HIGHMEM)
      list_add(&page->list, &free_normal_pages);
    else
      list_add(&page->list, &free_normal_pages); //todo free_high_pages, see test
  }
}

unsigned long get_free_page(int flags)
{
   page_t * page;
   struct list_head *list;
   
   if (flags & GFP_DMA)
     list = &free_dma_pages;
   else if (flags & (GFP_KERNEL | GFP_USER))
     list = &free_normal_pages;
   if (list_empty(list))
     return 0;
   page = list_entry(list->next, page_t, list);
   list_del(&page->list);
   page->count++;
   page->virt = _va(page->addr);
   //mmap_page(page->virt, page->addr, KERNEL_PAGE); 
   //zero_mem(page->virt,PAGE_SIZE);
   return page->virt;
}

void show_mem ()
{
  int i;
  int free_pages, used_pages, total_pages;
  
  free_pages = used_pages = total_pages = 0;
  for (i = 0; i < mem_map_len; i++) {
       if (is_page_free(&mem_map[i])) 
         free_pages++;
       else
         used_pages++;
       total_pages++;
  }
  int free = free_pages*PAGE_SIZE/1024;
  int used = used_pages*PAGE_SIZE/1024;
  int total = total_pages*PAGE_SIZE/1024;
  printk("Physical memory\n");
  printk ("%12s%12s%12s%12s\n", " ", "free", "used", "total");
  printk ("%12s%12d%12d%12d\n", "mem(kB):", free, used, total);
  printk ("%12s%12d%12d%12d\n", "pages:", free_pages, used_pages, total_pages);
}


