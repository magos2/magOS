#define KERNEL_DEBUG 0
#include <mm.h>
#include <page.h>
#include <pgtable.h>
#include <system.h>
#include <sched.h>
#include <errno.h>
#include <libc.h>
#include <string.h>
#include <kernel.h>

/*page fault error codes*/
#define PF_PRESENT  0x00000001
#define PF_WRITE    0x00000002
#define PF_USER     0x00000004
#define PF_RESERVED 0x00000008
#define PF_IF       0x00000010

extern page_t * mem_map;

unsigned long do_no_page(unsigned long address)
{
  unsigned long page;
  
  page = get_free_page (GFP_USER);
  if (!page)
    oom("do_no_page, vaddr=%d", address);
  mmap_page (address, _pa(page), PAGE_PRESENT|PAGE_RW|PAGE_USER);
  debug ("page %x mapped to vaddr %x", _pa(page), address);
  return _pa(page);
}

/*copy-on-write handler: the page is present but write protected.
 * in: <addr> virtual address causing the PF.
 *     <esp>
 * algorithm:
 *   - if old_page[addr].count == 1
         make <addr> writable in page table
         return
 *   - allocate <new_page> frame, map it to <addr>, with write access and
       copy content of old_page into new_page
 *   - decriment old_page.count
 */
unsigned long do_wp_page(unsigned long address)
{
  page_t *pg;
  unsigned long paddress, new_page;
  
  paddress = virt_to_phy(address);
  pg = &mem_map[PAGE_NR(paddress)];
  if (pg->count == 1) {
    mkwritable(address);
    return paddress;
  }
  else if (pg->count >= 2) {
    new_page = get_free_page (GFP_USER);
    if (!new_page)
      oom("in do_wp_page, vaddr=%d", address);
    memcpy ((char*)(address & PAGE_MASK), (char*)new_page, PAGE_SIZE);
    mmap_page (address, _pa(new_page), PAGE_PRESENT|PAGE_RW|PAGE_USER);
    debug ("do_wp_page: frame %x mapped to addr %x", _pa(new_page), address);
    pg->count--;
    return new_page;
  }
  else
    panic("do_wp_page must never go here!");
  return 0;
}

void pf_debug(unsigned long err, unsigned long address);   
void info_tlb(task_t *tsk);

/*Page Fault occurs when:
 *  - A page directory or table entry is not present in physical memory.
 *  - Attempting to load the instruction TLB with a translation for a non-executable page.
 *  - A protection check (privileges, read/write) failed.
 *  - A reserved bit in the page directory or table entries is set to 1.
 * The saved instruction pointer points to the instruction which caused the exception.
 * Error code
 * The Page Fault sets an error code:
   31              4               0
   +---+--  --+---+---+---+---+---+---+
   |   Reserved   | I | R | U | W | P |
   +---+--  --+---+---+---+---+---+---+
   Bit  Name
   P    Present : When set, the page fault was caused by a page-protection violation. When not set, it was caused by a non-present page.
   W    Write   : When set, the page fault was caused by a page write. When not set, it was caused by a page read.
   U    User    : When set, the page fault was caused while CPL = 3. This does not necessarily mean that the page fault was a privilege violation.
   R    Reserved write : When set, the page fault was caused by reading a 1 in a reserved field.
   I    Instruction Fetch  :When set, the page fault was caused by an instruction fetch.
 *In addition, it sets the value of the CR2 register to the virtual address which caused the Page Fault.
 *see http://wiki.osdev.org/Exceptions.
 *
 * esp: pointer on pt_regs saved by interrupt on stack.
 * err: error code
*/
void do_page_fault(unsigned long esp, unsigned long err)
{
  unsigned long address;
  asm ("mov %%cr2, %0":"=r"(address)::);
  struct pt_regs *regs = (struct pt_regs *)esp;
  if (address == 0) {
    oops(regs, esp);
    panic ("NullPointer Exception!");
  }
  
  pf_debug(err, address);
  
  if (!(err & PF_PRESENT)) {
    do_no_page (address);
    return;
  }
  else if ((err & (PF_PRESENT|PF_WRITE)) == (PF_PRESENT|PF_WRITE)) {
    do_wp_page(address);
    #if KERNEL_DEBUG
    info_tlb(current);
    #endif
    return;
  } else {
    oops(regs, esp);
    panic("Page fault type not handled: error code=%x", err);
  }
}

void pf_debug(unsigned long err, unsigned long address)
{
  char msg[128];
  strcpy("Page fault: [", &msg[0]);
  if (err & PF_USER)
    strcat(&msg[0], "user ");
  else
    strcat(&msg[0], "supervisor ");
  strcat(&msg[0], "tried to ");
  if (err & PF_WRITE)
    strcat(&msg[0], "write on ");
  else
    strcat(&msg[0], "read ");
  strcat(&msg[0], "%8x, ");
  if (err & PF_PRESENT)
    strcat(&msg[0], "a present page, caused protection violation, ");
  else
    strcat(&msg[0], "non-present page");
  strcat(&msg[0], "]");
  debug(&msg[0], address);
}










