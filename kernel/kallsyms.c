/* By Abderrahim Rahali @2016
 *
 * this is a helper to search kernel symbols by its addresses
 */
#include <types.h>
#include <string.h>
#include <libc.h>
#include <mm.h>

#define KSYM_MAX_LEN   48
 
/*this will be linked to theire real values in the second stage*/
extern unsigned long kallsyms_addresses[] __attribute__((weak));
extern char kallsyms_names[] __attribute__((weak));
extern int kallsyms_num_syms; /*number of syms*/

char *next_str( char* s)
{
  char *tmp;
  for(tmp=s;*tmp;tmp++);
  tmp++;
  return tmp;
}

char *get_kallsyms_name (int n)
{
  int i = 0;
  char* s = &kallsyms_names[0];
  do {
    if (i == n)
      return s;
    s = next_str(s);
    i++;
  } while(1);
}

/*find kernel symbol by address <addr>
 *  parcourir la table kallsyms_addresses,
      si kallsyms_addresses[i] == addr
        return kallsyms_names[i]
    ici non trouve, return NULL
 */
void ksym_lookup(unsigned long addr, char* buf)
{
  int i, ksym_len;
  unsigned long diff;
  char *ksym_name;
  buf[0] = '\0';
  i = kallsyms_num_syms - 1;
  while (i >= 0) {
    if (kallsyms_addresses[i] <= addr) {
      ksym_name = get_kallsyms_name(i);
      ksym_len = strlen(ksym_name);
      strncpy(ksym_name, &buf[0], ksym_len);
      diff = addr - kallsyms_addresses[i];
      buf[ksym_len] = '\0';
      if (diff > 0) {
        buf[ksym_len++] = '/';
        buf[ksym_len++] = '+';
        buf[ksym_len++] = '0';
        buf[ksym_len++] = 'x';
        itoa(&buf[ksym_len++], diff, 16);
      }
      return;
    }
    i--;
  }
}

