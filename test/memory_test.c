typedef int wchar_t; /*for unit test compile*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mm.h"
   
extern int mem_map_len;

int mmap_pages (unsigned long vaddr, int nr, int flags)
{
  return 0;
}

void unmap_pages (unsigned long vaddr, int nr) {}

void mmap_page (unsigned long vaddr, unsigned long paddr, int flags){}
void unmap_page (unsigned long vaddr){}

int main(void)
{ 
  unsigned long start_mem, end_mem, mem_size = 8*1024*1024, malloc_start, addr;
  
  malloc_start = (unsigned long)malloc(mem_size);
  start_mem = malloc_start;
  end_mem = start_mem + mem_size;
  
  printf ("start_mem=%#lx, end_mem=%#lx, mem_size=%#lx\n",start_mem, end_mem, mem_size);
  
  start_mem = mem_init(start_mem, end_mem);
  
  printf ("after mem_init : start_mem=%#lx, mem_map_len=%d\n",start_mem, mem_map_len);
  
  show_mem ();
  
  addr = get_free_page(GFP_KERNEL);
  printf("allocated page : va=%lx, pa=%lx\n", addr, _pa(addr));
  free_page(addr);
    
  int i = 10;
  printf(">>> allocating 10 pages\n");
  while(i--) {
    addr = get_free_page(GFP_KERNEL);
    printf("va=%lx, pa=%lx\n", addr, _pa(addr));
  }
  printf("\n");
  show_mem ();
  
  i = 100;
  printf(">>> allocating and freeing 100 pages!!!");
  while(i--) {
    addr = get_free_page(GFP_KERNEL);
    free_page(addr);
  }
  printf("\n");
  
  show_mem ();
  
  printf(">>> allocating all pages");
  do {
    addr = get_free_page(GFP_KERNEL);
    //printf(" %lx", addr);
  }while (addr);
  printf("\n");
  
  show_mem ();
  
  free((char*)malloc_start);
  
  return 0;
}
