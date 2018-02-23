/*_ Copyright 2016 @AR
 * 
 * vmalloc : kernel page heap allocator
 */
#include <mm.h>
#include <page.h>
#include <pgtable.h>
#include <kernel.h>

struct list_head free_area_list; /*free list of vm areas*/
struct list_head used_area_list;

/* allouer une area de taille <size>, et retourner un pointeur sur cette zone allouee
     chercher une free area qui a une taille > size
       addr = area.start
       si area.size == size
         move <area> from free list to used list
       si area.size > size
         area.start += size
         allocate new_area in kheap
         add new_area to used list
       return <addr>
 */
void * vmalloc(size_t size)
{
  vm_area_t *area, *new_area;
  struct list_head* p;
  int nr;
  
  size = PAGE_ALIGN(size);
  nr = MAP_NR(size) + 1;
  list_for_each (p, &free_area_list) {
    area = list_entry(p, vm_area_t, list);
    if (size == area->vm_end - area->vm_start) {
      list_del(&area->list);
      list_add(&area->list, &used_area_list);
      mmap_pages(area->vm_start, nr, PAGE_KERNEL);
      return (void *)area->vm_start;
    }
    else if (size < area->vm_end - area->vm_start) {
      new_area = (vm_area_t *)kmalloc(sizeof(vm_area_t), GFP_KERNEL);
      new_area->vm_start = area->vm_start;
      new_area->vm_end = new_area->vm_start + size;
      list_add(&new_area->list, &used_area_list);
      area->vm_start += size;
      mmap_pages(new_area->vm_start, nr, PAGE_KERNEL);
      return (void *)new_area->vm_start;
    }
  }
  return NULL;
} 

/* liberer une area, starting at <addr>
     a1. search area in used list
     a2. unmap area, to free associated frames
     a3. while area.next is free, do
           merge area and area.next
           area.size += area.next.size
           del area.next from free list
           kfree(area.next)  
     a4. move area from used to free list
 */
void vfree(void * addr)
{
  struct list_head *p, *fp;
  vm_area_t *area, *f_area;
  int nr;
  
  list_for_each (p, &used_area_list) {
    area = list_entry(p, vm_area_t, list);
    if (area->vm_start == (unsigned long)addr) 
      break;
  }
  if (!area)
    return;
  nr = MAP_NR(area->vm_end - area->vm_start) + 1;
  unmap_pages((unsigned long)addr, nr);
  list_for_each (fp, &used_area_list) {
    f_area = list_entry(fp, vm_area_t, list);
    if (area->vm_end == f_area->vm_start) {
      area->vm_end = f_area->vm_end;
      list_del(&f_area->list);
      kfree(f_area);
    }
  }
}

void show_page_heap ()
{
  vm_area_t* area;
  struct list_head *p;
  int npages, nfree = 0;
  
  printk("free page list [vm_start, end, npages]: ");
  list_for_each (p, &free_area_list) {
    area = list_entry(p, vm_area_t, list);
    npages = (area->vm_end - area->vm_start)/PAGE_SIZE;
    printk("[%x,%x,%d]", area->vm_start, area->vm_end, npages);
    nfree += npages;
  }
  printk("\n");
  printk("nb of free pages: %d\n\n", nfree);
}

void vmalloc_init(unsigned long kheap_pg_start, unsigned long kheap_pg_end)
{
  vm_area_t* area;
  
  INIT_LIST_HEAD(&free_area_list);
  area = (vm_area_t *)kmalloc(sizeof(vm_area_t), GFP_KERNEL);
  area->vm_start = kheap_pg_start;
  area->vm_end = kheap_pg_end;
  list_add(&area->list, &free_area_list);
}
