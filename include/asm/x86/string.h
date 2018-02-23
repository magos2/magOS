#ifndef MAGOS_STRING_H
#define MAGOS_STRING_H
/*
** Copyright 2016 @AR
**
** definition les fonctions principales de maniplation des strings. Il seront tres rapides.
** On suppose que ES=DS
*/   
#include <types.h>

static inline  char *  strcpy(const char * src, char *dst)
{
   __asm__ volatile (
      "cld\n"
      "1:lodsb\n\t" 
      "stosb\n\t"
      "test %%al, %%al\n\t"
      "jne 1b"         
      :/* no output*/
      :"S"(src),"D"(dst)
      :"0", "1", "memory"
   );
   return dst;
} 

static inline  char *  strncpy(const char *src, char *dst, int count)
{
   __asm__ volatile ( 
      "cld             \n\t"  
      "1: dec %2       \n\t"
      "js 2f           \n\t"
      "lodsb           \n\t" 
      "test %%al, %%al \n\t"
      "je 2f           \n\t"
      "stosb           \n\t"
      "jmp 1b          \n\t"
      "2: mov $0, %%al\n\t"     
      "   stosb"    
      :/* no outputs*/
      :"S"(src),"D"(dst), "c"(count)
      :"0", "1", "3", "memory"
   );
   return dst; 
 }


static inline  int strlen(char *s)
{
   int len=0;
   __asm__ volatile (
        "cld              \n\t"
        "mov $0, %%ecx    \n\t"
        "1:lodsb          \n\t"
        "inc %%ecx        \n\t"
        "testb %%al, %%al \n\t"
        "jne 1b           \n\t"
        "dec %%ecx        \n\t"
        :"=S"(s),"=c"(len)
        :"0"(s)
        :"0", "1", "memory" );
   return len;
}   

/*concatenate S1 and S2. result go in S1 */
static inline  char * strcat(char *s1, char *s2)
{
   __asm__ volatile (
         "cld\n"  
         "1:lodsb\n\t"
         "testb %%al, %%al\n\t"
         "jne 1b\n\t"
         "dec %%esi\n\t"
         "mov %%esi, %%eax\n\t"
         "mov %%edi, %%esi\n\t"
         "mov %%eax, %%edi\n\t"
         "2:lodsb\n\t"
         "stosb\n\t"
         "testb %%al, %%al\n\t"
         "jne 2b\n\t"         
         :
         :"S"(s1), "D"(s2)
         :"0", "1", "memory" 
      );
   return s1;
}  

/* return value :
 * <0	the first character that does not match has a lower value in str1 than in str2
 *  0	the contents of both strings are equal
 * >0	the first character that does not match has a greater value in str1 than in str2
 */   
static inline  int strncmp (char* s1, char* s2, size_t len)
{
  int i;
  char c1, c2;
  
  for (i=0; i < len; i++) {
    c1 = *(s1 + i);
    c2 = *(s2 + i);
    if (c1 < c2) return -1;
    if (c1 > c2) return 1;
    if (c1 == '\0' && c2 == '\0') return 0;
  }
  return 0;
}

static inline  int strcmp (char* s1, char* s2)
{
  char * p1;
  char * p2;
  
  p1 = s1;
  p2 = s2;
  for (;;) {
    if (*p1 < *p2) return -1;
    if (*p1 > *p2) return 1;
    if (*p1 == '\0' && *p2 == '\0') return 0;
    p1++;
    p2++;
  }
  return 0;
}

#endif
