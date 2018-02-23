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
  unsigned long start_mem, end_mem;
  unsigned long  mem_size = 8*1024*1024, malloc_start;
  
  malloc_start = (unsigned long)malloc(mem_size);
  start_mem = malloc_start;
  end_mem = start_mem + mem_size;
  end_mem &= PAGE_MASK;
  
  printf ("start_mem=%#lx, end_mem=%#lx, mem_size=%#lx\n",start_mem, end_mem, mem_size);
  start_mem = mem_init(start_mem, end_mem);
  printf ("after mem_init : start_mem=%#lx, mem_map_len=%d\n",start_mem, mem_map_len);
  show_mem ();
  
  kmalloc_init (start_mem, end_mem);
  show_kheap();
  
  int *p = (int *)kmalloc(sizeof(int), GFP_KERNEL);
  vm_area_t* area=(vm_area_t*)kmalloc(sizeof(vm_area_t), GFP_KERNEL);
  mm_t* mm=(mm_t*)kmalloc(sizeof(mm_t), GFP_KERNEL);
  char *s = (char*)kmalloc(sizeof(char)*4072, GFP_KERNEL);
  printf("kallocated p=%p, area=%p, mm=%p, s=%p\n", p, area, mm, s); 
  show_kheap();
  
  kfree(mm);
  kfree(area);
  kfree(s);
  show_kheap();
  
  kmalloc(sizeof(char)*4096, GFP_KERNEL);
  return 0;
}