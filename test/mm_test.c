typedef int wchar_t; /*for unit test compile*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "mm.h"
   
unsigned long start_mem, end_mem;
pde_t swapper_pg_dir[1024];

unsigned long get_free_page(int flags)
{
  unsigned long addr;
  addr = start_mem;
  start_mem += PAGE_SIZE;
  return addr;
}

void free_page(unsigned long addr) 
{
  
}
void kmalloc_init (unsigned long brk_start, unsigned long brk_end) {}
void vmalloc_init(unsigned long kheap_pg_start, unsigned long kheap_pg_end) {}
 

void test_paging_init()
{
  int i, j;
  pde_t *pgdp;
  pte_t *pgtablep;
  
  printf("----- Begin test_paging_init -----\n");
  size_t mem_size = 4*1024*1024;
  start_mem = (unsigned long) malloc(mem_size);
  end_mem = start_mem + mem_size - 1;
  printf("before paging_int, start_mem=%lx, end_mem=%lx\n", start_mem, end_mem);
  start_mem = paging_init(start_mem, end_mem);
  printf("after paging_int,  start_mem=%lx, end_mem=%lx\n", start_mem, end_mem);
  pgdp = swapper_pg_dir + 768;
  for (i=0; i<5; i++, pgdp++) {
    printf("swapper_pg_dir[%d]=%#lx\n", 768+i, (unsigned long)pgd_get(pgdp));
    pgtablep = pgd_page(pgdp);
    for (j=0; j < 5; j++, pgtablep++)
      printf("   pgtable[%d]=%#lx\n", j, (unsigned long)pte_get(pgtablep));
  }
  printf("----- End test_paging_init -----\n");
}

void test_copy_page_tables() 
{
  pde_t *pgd1, *pgd2;
  pte_t *pgtable_0, *pgtable_100, *pgtable_768;
  pte_t *pgtable2_0, *pgtable2_100, *pgtable2_768;
  
  printf("----- Begin test_copy_page_tables -----\n");
  pgd1 = pgd_alloc();
  pgtable_0 = page_table_alloc(pgd1);
  pte_set(pgtable_0+5, 0x78000|PAGE_PRIVATE);
  pgtable_100 = page_table_alloc(pgd1 + 100);
  pte_set(pgtable_100+400, 0x78000|PAGE_SHARED);
  pgtable_768 = pgd_page(pgd1+768);
  printf("pgd1:\n");
  printf("  pgd1[0]=%#x, pgtable_0[5]=%#x\n", (int)pgd_get(pgd1), (int)pte_get(pgtable_0+5));
  printf("  pgd1[100]=%#x, pgtable_100[400]=%#x\n", (int)pgd_get(pgd1+100), (int)pte_get(pgtable_100+400));
  printf("  pgd1[768]=%#x, pgtable_768[1]=%#x\n", (int)pgd_get(pgd1+768), (int)pte_get(pgtable_768+1));
  pgd2 = pgd_alloc();
  copy_page_tables(pgd1, pgd2);
  pgtable2_0 = pgd_page(pgd2);
  pgtable2_100 = pgd_page(pgd2+100);
  pgtable2_768 = pgd_page(pgd2+768);
  printf("pgd2:\n");
  printf("  pgd2[0]=%#x, pgtable2_0[5]=%#x\n", (int)pgd_get(pgd2), (int)pte_get(pgtable2_0+5));
  printf("  pgd2[100]=%#x, pgtable2_100[400]=%#x\n", (int)pgd_get(pgd2+100), (int)pte_get(pgtable2_100+400));
  printf("  pgd2[768]=%#x, pgtable2_768[1]=%#x\n", (int)pgd_get(pgd2+768), (int)pte_get(pgtable2_768+1));
  printf("----- End test_copy_page_tables -----\n");
}

int main(void)
{
  pde_t* pgd;
  pte_t* pgtable1, *pgtable2;
  
  test_paging_init();
  
  printf("----- Begin test of pgd/table alloc and free -----\n");
  printf("allocate pgdir\n");
  pgd = pgd_alloc();
  printf(" pgd[0]=%#x\n",  (int)*pgd);
  printf(" pgd[1]=%#x\n",  (int)*(pgd+1));
  printf(" pgd[768]=%#x\n", (int)pgd[768]);
  printf(" pgd[1023]=%#x\n", (int)*(pgd+1023));
  
  pgtable1 = page_table_alloc(pgd+1);
  printf("allocated pgtable1 : pgd[%d]=%#x, pgtable1[0]=%x\n", 1, (int)pgd_get(pgd+1), (int)*pgtable1);
  pgtable2 = page_table_alloc(pgd+2);
  printf("allocated pgtable2 : pgd[%d]=%#x, pgtable2[1023]=%x\n", 2, (int)pgd_get(pgd+2), (int)pgtable2[1023]);
  page_table_free(pgd+1);
  printf("freed pgtable1 : pgd[%d]=%#x, pgtable1=%p\n", 1, (int)pgd_get(pgd+1), pgtable1);
  printf("free pgdir\n");
  pgd_free(pgd);
  
  test_copy_page_tables();
  return 0;
}






