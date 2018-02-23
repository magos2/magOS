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
   return dst;
} 

static inline  char *  strncpy(const char * src, char *dst, int count)
{
   return dst; 
 }


static inline  int strlen(char *s)
{
   int len=0;
   return len;
}   

static inline  char * strcat(char *s1, char *s2)
{
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
