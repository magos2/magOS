#ifndef MAGOS_PAGE_H
#define MAGOS_PAGE_H
#include <list.h>
#include <segment.h>

#define PAGE_SIZE  4096  /* Pages de 4ko */
#define PAGE_SHIFT 12   /* pour frame de 4ko */
#define PAGE_MASK  0xFFFFF000

#define PAGE_NR(addr)  ((addr) >> PAGE_SHIFT) /*phy frame*/

/*Align addr to next page boundary */ 
#define PAGE_ALIGN(addr)  (((addr) + PAGE_SIZE - 1) & PAGE_MASK)

#define _pa(vaddr)  ((vaddr) - PAGE_OFFSET) /*vaddr to phy addr, in kernel address space*/
#define _va(paddr)  ((paddr) + PAGE_OFFSET) /*phy addr to vaddr in kernel space*/


/*physical frame descriptor*/
struct page {
  unsigned long addr;
  struct list_head list;
  int count; /*nb of references on this page*/
  int flags; /*PG_reserved, locked....*/
  int prot;/*rwx protections*/
  unsigned long virt; /*virtual addr*/
};

typedef struct page page_t;

/*page flags*/
#define PG_reserved  0x00000001
#define PG_locked    0x00000002

#define is_page_free(page)  ((page)->count == 0)
#define set_page_reserved(page)  ((page)->flags |= PG_reserved)

#define zero_page(addr)   \
        __asm__ ("rep stosb"::"a"(0), "D"(addr),"c"(PAGE_SIZE));
  
#ifdef KERNEL_UNIT_TEST
/*this will redefine _pa, _va macros, so we can test methods in userspace*/
#include "../test/include/page_test.h"
#endif

#endif



