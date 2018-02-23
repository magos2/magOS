#ifndef _PGTABLE_H
#define _PGTABLE_H

/* Page Directory and Page Table Entries Flags */
#define PAGE_PRESENT     0x00000001   /* page present in memory*/
#define PAGE_RW          0x00000002   /* read/write mode. rw if set.*/
#define PAGE_USER        0x00000004   /* 1 if user mode, 0 if supervisor*/
#define PAGE_PWT         0x00000008   /* for PGD Entry*/
#define PAGE_PCD         0x00000010   /* PGD Entry: 1: page table will be cached*/
#define PAGE_ACCESSED    0x00000020   /* set by the processor, 1 if page accessed*/
#define PAGE_DIRTY       0x00000040   /* set by the processor, 1 if page has been written to*/
#define PAGE_PS          0x00000080   /* PGD only : page size 0 pour 4k, 1 pour 4M*/
#define PAGE_COW         0x00000200  /* copy-on-write : implemented in software (one of the AVL bits)*/

#define PAGE_PRIVATE          (PAGE_PRESENT | PAGE_RW | PAGE_USER | PAGE_ACCESSED)
#define PAGE_READONLY         (PAGE_PRESENT | PAGE_USER | PAGE_ACCESSED)
#define PAGE_SHARED           (PAGE_PRESENT | PAGE_RW | PAGE_USER | PAGE_ACCESSED | PAGE_COW)
#define PAGE_KERNEL           (PAGE_PRESENT | PAGE_RW | PAGE_ACCESSED)

#define PGD_MASK 0xFFC00000

#define PTRS_PER_PGD  1024
#define PTRS_PER_PGT  1024

#define pgd_index(addr) ((addr) >> 22)
#define pte_index(addr) (((addr) >> 12) & 0x3FF)

/*return pde_t*,  sur une entree de la table pgd[1024]
 */
#define pgd_offset(pgd, addr) (pgd + pgd_index(addr))

/*return pte_t*, sur une entree de la table pgtable[1024]
 */
#define pte_offset(pgtable, addr) (pgtable + pte_index(addr))

#define pgd_page(pgdptr)  (pte_t *)_va(*(pgdptr) & PAGE_MASK)
#define pte_page(pgtableptr)  (unsigned long)_va(*(pgtableptr) & PAGE_MASK)

#define pgd_get(pgdptr)  *(pgdptr)
#define pte_get(pgtableptr)  *(pgtableptr)

#define pgd_set(pgdptr, val)  (*(pgdptr) = val)
#define pte_set(pgtableptr, val)  (*(pgtableptr) = val)

#define pgd_present(pgdptr)  ((*(pgdptr) & PAGE_PRESENT)?1:0)
#define pte_present(pgtableptr)  ((*(pgtableptr) & PAGE_PRESENT)?1:0)

#define pgd_clear(pgdptr)   pgd_set(pgdptr, 0)
#define pte_clear(pgtableptr)  pte_set(pgtableptr, 0)

#define addr_to_pte(addr) ({                                        \
                               pde_t *pgdir;                        \
                               pte_t *pgtable;                      \
                               pgdir = current->mm.pgdir;           \
                               pgdir = pgd_offset(pgdir, addr);     \
                               pgtable = pgd_page(pgdir);           \
                               pgtable = pte_offset(pgtable,addr);  \
                               pgtable;})
                               
#define virt_to_phy(addr) ({unsigned long paddr, page;           \
                            pde_t *pgdir;                        \
                            pte_t *pgtable;                      \
                            pgdir = current->mm.pgdir;           \
                            pgdir = pgd_offset(pgdir, addr);     \
                            pgtable = pgd_page(pgdir);           \
                            pgtable = pte_offset(pgtable,addr);  \
                            page = pte_get(pgtable) & PAGE_MASK; \
                            paddr = page | (addr & ~PAGE_MASK);  \
                            paddr;})
                            
#define mkwritable(addr)  ({pte_t *pgtable;              \
                            pgtable = addr_to_pte(addr); \
                            *pgtable |= PAGE_RW;         \
                           })
                            
#endif