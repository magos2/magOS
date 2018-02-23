#ifndef PAGE_TEST_H
#define PAGE_TEST_H
/*this header redefines somme macros( _pa, _va) , so we can test methods in userspace
 * see page.h.
 * you must compile with -DKERNEL_UNIT_TEST
 */
#undef _pa
#undef _va

#define _pa(vaddr)  (vaddr) 
#define _va(paddr)  (paddr)


#endif