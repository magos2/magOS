/* Copyrigth 2016 @AR
 *
 * virtual memory manager:
 *  pgdir_alloc/free : alloc and free page directory
 *  page_table_alloc/free
 *  copy_page_tables : from a directory to another
 *  map_page(paddr, vaddr) : map vaddr to paddr. see unmap.
 *  
*/
#define KERNEL_DEBUG 0
#include <mm.h>
#include <page.h>
#include <pgtable.h>
#include <system.h>
#include <sched.h>
#include <errno.h>
#include <libc.h>
#include <kernel.h>

extern page_t * mem_map;

/* paging init : initialise the kernel adrtress space {swapper_pg_dir}
     - swapper_pg_dir maps all physical memory from 0xC0000000 to 0xC0000000+end_mem
     - create page tables if necessary for mapping.
     - fist 4mB are already mapped in head.S
     - if you have 2GB phisycal memory, you need 1MiB to map all memory!
 */
unsigned long paging_init (unsigned long start_mem, unsigned long end_mem)
{
  pde_t *pgdptr;
  pte_t *pgtable;
  unsigned long addr; 	
  int i;
  
  end_mem &= PAGE_MASK;
  start_mem = PAGE_ALIGN(start_mem);
  pgdptr = swapper_pg_dir + 768;
  addr = 0;
  while(addr < end_mem) {
    if (!pgd_present(pgdptr)) {
      pgtable = (pte_t *)start_mem;
      pgd_set(pgdptr, (unsigned long)pgtable | PAGE_KERNEL);
      start_mem += PAGE_SIZE;
      for (i=0; i < 1024 && addr < end_mem; i++, pgtable++, addr += PAGE_SIZE)
        pte_set(pgtable, addr | PAGE_KERNEL);
    }
    else
      addr += PAGE_SIZE*1024;
    pgdptr++;
  }
  info ("Paging initialized.");
  return start_mem;
}

pte_t* page_table_alloc (pde_t* pgdptr)
{
  pte_t *pgtable;
  
  if (pgd_present(pgdptr))
    return pgd_page(pgdptr);
  pgtable = (pte_t *)get_free_page(GFP_KERNEL);
  if (!pgtable)
    return NULL;
  zero_page (pgtable);	
  pgd_set(pgdptr, _pa((unsigned long)pgtable) | PAGE_PRIVATE);
  return pgtable;
}

void page_table_free (pde_t* pgdptr)
{
  int i;
  pte_t *pgtable, *pgtablep;
  
  if (!pgd_present(pgdptr))
    return;
  pgtable = pgd_page(pgdptr);
  pgtablep = pgtable;
  for (i=0; i < 1024; i++, pgtablep++) {
    if (pte_present(pgtablep)) 
      free_page(pte_page(pgtablep));
  }
  free_page((unsigned long)pgtable);
  pgd_clear(pgdptr);
}

pde_t * pgdir_alloc()
{
  pde_t *pgdir;
  
  pgdir = (pde_t *)get_free_page(GFP_KERNEL);
  if (!pgdir)
    return NULL;
  zero_page(pgdir);
  return pgdir;
}

void pgdir_free (pde_t* pgdir)
{
  int i;
  pde_t *pgdp;
  
  pgdp = pgdir;
  for (i=0; i<768; i++, pgdp++) 
    if (pgd_present(pgdp))
      page_table_free(pgdp);
  free_page((unsigned long)pgdir);
}

/* mapper une page virtual a un frame.
  input : vaddr, paddr, flags
  output : mapper vaddr a paddr
 */
void mmap_page (unsigned long vaddr, unsigned long paddr, int flags)
{
  pde_t *pgdir, *pgdp;
  pte_t *pgtable = NULL, *pgtablep;
  
  pgdir =  current->mm.pgdir;
  pgdp = pgd_offset(pgdir, vaddr);
  if (!pgd_present(pgdp))  /*if page table dont exist, create one*/
    pgtable = page_table_alloc(pgdp);
  pgtable = pgd_page(pgdp);
  if (!pgtable) {
    panic("error in mmap, cannot allocate page table, vaddr=%x, paddr=%x, flags=%x", vaddr, paddr, flags);
    return;
  }
  pgtablep = pte_offset(pgtable, vaddr);
  paddr &= PAGE_MASK;
  pte_set(pgtablep, paddr | flags);
}

/* mmap <nr> pages starting at vaddr
 */
int mmap_pages (unsigned long vaddr, int nr, int flags)
{
  unsigned long page;
  
  while (nr-->0) {
    page = get_free_page(GFP_KERNEL);
    if (!page)
      return -ENOMEM;
    mmap_page(vaddr + nr*PAGE_SIZE, page, flags);
  }
  invalidate();
  return 0;
}

/* Algo 
  u0 : trouver la page_table mappant la page
  u1 : si la virtual page n est pas mappé, ne rien faire.
  u2 : unmap the page
      - liberer la page physique
      - vider l entree correspondante dans la page_table
 */
void unmap_page (unsigned long vaddr)
{
  pde_t *pgdir;
  pte_t *pgt;
  int pde, pte;
  
  pgdir = (pde_t *)0xFFFFF000;
  pgt = (pte_t *)((vaddr & 0xFFC00000) | 0x003FF000);
  pde = pgd_index(vaddr);
  pte = pte_index(vaddr);
  if (!(pgdir[pde] & PAGE_MASK) || !(pgt[pte] & PAGE_MASK))
   return;
  pgt[pte] = PAGE_SHARED;
}

/*unmap <nr> pages starting at vaddr*/
void unmap_pages (unsigned long vaddr, int nr)
{
  while (nr-->0) 
    unmap_page(vaddr + nr*PAGE_SIZE);
}

/*create a new region within the process linear address space  */
void mmap(void)
{
}

void munmap()
{
}

/* copy page tables from current(parent) to child.
   Algo:
     vars:
       new_pgdir: <tsk> page directory
       old_pgdir: <current> page directory
     - allocate a <new_pgdir>
     - walk in <old_pgdir>, 
         if entry is present[old_pgtable]: then
           allocate a <new_pg_table>
           walk in  <old_pgtable>:
             if entry[old_pte] is present and readonly
               new_pte = old_pte
             if entry[old_pte] is present and writable
               make old_pte readonly
               new_pte = old_pte
             mem_map[old_pte].count++
   pour la partie kernel, on ne copie que les reference des pgtables
 */
int copy_page_tables (task_t *tsk)
{
  int i,j;
  pde_t *old_pgdir, *new_pgdir; 
  pte_t *old_pgtable, *new_pgtable;
  page_t *page;
  
  old_pgdir = current->mm.pgdir;
  new_pgdir = pgdir_alloc();
  if (!new_pgdir)
    return -ENOMEM;
  tsk->mm.pgdir = new_pgdir;
  for (i=0; i < 768; i++,old_pgdir++,new_pgdir++) {
    if (!pgd_present(old_pgdir))
      continue;
    if ((*old_pgdir & PAGE_USER) == 0) {
      *new_pgdir = *old_pgdir;
      continue;
    }
    old_pgtable = pgd_page(old_pgdir);
    new_pgtable = page_table_alloc(new_pgdir);
    if (!new_pgtable)
      return -ENOMEM;
    pgd_set(new_pgdir, _pa((unsigned long)new_pgtable) | PAGE_PRIVATE);
    for (j=0; j < 1024; j++,old_pgtable++,new_pgtable++) {
      if (!pte_present(old_pgtable))
        continue;
      page = &mem_map[PAGE_NR(*old_pgtable)];
      if ((*old_pgtable & (PAGE_USER|PAGE_RW|PAGE_PRESENT)) == (PAGE_USER|PAGE_PRESENT)) {//present & readonly
        *new_pgtable = *old_pgtable;
        page->count++;
      }
      else if ((*old_pgtable & (PAGE_USER|PAGE_RW|PAGE_PRESENT)) == (PAGE_USER|PAGE_RW|PAGE_PRESENT)) {//present & rw
        *old_pgtable &= ~PAGE_RW; /*make entry readonly*/
        *new_pgtable = *old_pgtable;
        page->count++;
      }
    }
  }
  /*refence kernel space*/  
  for (i=768; i < 1024; i++, old_pgdir++, new_pgdir++) 
    *new_pgdir = *old_pgdir;
  invalidate();
  return 0;
}

void info_tlb(task_t *tsk)
{
  int i,j;
  pde_t *pgdir; 
  pte_t *pgtable;
  unsigned long paddr, vaddr;
  
  printk("Task <%d>, virtual to physical address mapping:\n", tsk->pid);
  pgdir = tsk->mm.pgdir;
  for (i=0; i < 1024; i++,pgdir++) {
    if (pgd_present(pgdir) && (*pgdir & PAGE_USER)) {
      pgtable = pgd_page(pgdir);
      for (j = 0; j < 1024; j++, pgtable++) {
        if (pte_present(pgtable)) {
          vaddr = (i << 22) + (j << 12);
          paddr = pte_get(pgtable);
          printk(" | %8x --> %8x\n", vaddr, paddr); 
        }
      }
    }
  }
}

