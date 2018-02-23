#ifndef MAGOS_MM_H
#define MAGOS_MM_H

#include <types.h>
#include <segment.h>
#include <list.h>
#include <page.h>
#include <pgtable.h>
#include <ptrace.h>

#define MAP_NR(vaddr) (_pa(vaddr) >> PAGE_SHIFT)  /*virtual page number in kernel space?*/ 
#define MAP_ADDR(page_nr) ((page_nr) << PAGE_SHIFT)

#define RAM_MAXPAGE (0xffffff >> PAGE_SHIFT) /* 16 Mo de RAM max pour le moment*/ 

#define LD_ENTRY  0x400000 /*programms will be loaded at this address*/

#define START_LOW_MEM 0x100000  /*low mem start at 1MB*/

#define ZONE_DMA      0x0         /*Zone de 0 a 16Mo, limité par Bus ISA, identity mapping*/
#define ZONE_NORMAL   0x1000000   /*Zone de 16 a 896Mo, identity mapping*/
#define ZONE_HIGHMEM  0x38000000  /*Zone audela de 896M*/

#define DMA_START       0x100000      //DMA : 1MB-16MB
#define DMA_END         0x1000000     
#define VMALLOC_START   0x1000000     //KERNEL PAGES HEAP : 16MB-256MB
#define VMALLOC_END     0x10000000    
#define KMALLOC_START   0x10000000    //KERNEL HEAP : 256MB-1GB
#define KMALLOC_END     0x40000000

#define RESERVED_PAGES (16 + 16) /* 64k(16 pages) for kernel code, 64k for kstack */

#define SWAPPER_PG_DIR 0x1000

/*get_free_page flags*/
#define GFP_DMA    0x00
#define GFP_KERNEL 0x01
#define GFP_USER   0x02


typedef unsigned long  pde_t; /*page directory entry*/
typedef unsigned long  pte_t; /*page table entry*/

extern pde_t swapper_pg_dir[1024] ; /*kernel page directory*/
extern pte_t pgt0[1024];    /*kernel first 4MB.  identity map*/

/* virtual memory area */
struct vm_area_struct {
  unsigned long vm_start; /* start and end address of this area*/
  unsigned long vm_end;  
  struct list_head list; /*vm_next, vm_prev*/
  
  int vm_prot; /* protection:r/w/x?...*/
  int vm_flags; /*anonymos area, file backed, ...*/
};

typedef struct vm_area_struct vm_area_t;

/*vm_area flags*/
#define VM_READ       0x01
#define VM_WRITE      0x02
#define VM_EXEC       0x04
#define VM_SHARED     0x08
#define VM_GROWS_DOWN 0x10  /*stack vm_area*/

/*memory management*/
struct mm_struct {
  vm_area_t *mmap; /*list of VMAs*/
  int map_count;  /*number of VMAs*/
  
  pde_t *pgdir; /* task page directory */
   
  unsigned long start_code, end_code, start_data, end_data; /*code, data*/
  unsigned long start_brk, brk, start_stack, end_stack; /*heap, stack*/
  unsigned long start_arg, end_arg, start_env, end_env;
};

typedef struct mm_struct  mm_t;   

/* memory.c */
unsigned long  get_free_page(int flags); /*renvoie une frame physique libre */
void free_page(unsigned long addr);
unsigned long mem_init(unsigned long start_mem, unsigned long end_mem);
void show_mem(void);

/*get a zeroed free page*/
inline static unsigned long __get_free_page(int flags)
{
  unsigned long addr = get_free_page(flags);
  zero_page(addr);
  return addr;
}

/* mm.c */
unsigned long paging_init(unsigned long mem_start, unsigned long mem_end);
unsigned long mm_init (unsigned long start_mem, unsigned long end_mem);
void mmap_page (unsigned long vaddr, unsigned long paddr, int flags);
void unmap_page (unsigned long vaddr);
int mmap_pages (unsigned long vaddr, int nr, int flags);
void unmap_pages (unsigned long vaddr, int nr);
void do_page_fault(unsigned long esp, unsigned long error_code);
pde_t * pgdir_alloc();
void pgdir_free (pde_t* pgdir);
pte_t* page_table_alloc (pde_t* pgdptr);
void page_table_free (pde_t* pgdptr);

/*mmap.c*/
struct file ;
int generic_mmap (struct file *fp);

/*fork.c*/
pid_t do_fork(struct pt_regs *regs);

/*exec.c*/
void do_execv(char *filename, struct pt_regs *regs);

/*exit.c*/
void do_exit ();

/*kmalloc.c*/
void kmalloc_init (unsigned long brk_start, unsigned long brk_end);
int ksbrk (int n, int order, int flags);
void * kmalloc(size_t size, int flags); 
void kfree(void * addr); 
void show_kheap();

/*vmalloc.c*/
void * vmalloc(size_t size); 
void vfree(void * addr); 
void vmalloc_init(unsigned long kheap_pg_start, unsigned long kheap_pg_end);
void show_page_heap();

#endif
