#ifndef MAGOS_BITOPS_H
#define MAGOS_BITOPS_H

/* Copyright 2016 @AR
 *
 * set_bit : met à 1 un bit
 * clear_bit
 */
#include "errno.h" 

#define mask(n) (1 << (n & 0x1f))  
#define test_bit(nr, addr) !!(*(addr + (nr >> 5)) & mask(nr))

static void inline set_bit(int nr, int *addr)
{
   *(addr + (nr >> 5)) |= mask(nr);
}

static void inline clear_bit(int nr, int *addr)
{
   *(addr + (nr >> 5)) &= ~mask(nr);
}

/* find first zero bit at addr */ 
static int inline find_first_zero_bit(int nbits, int *addr)
{
   int i;
   for (i=0; i < nbits; i++)
      if (test_bit(i, addr) == 0)
         return i;
   return -EAGAIN;
} 

/* find first set bit at addr */ 
static int inline find_first_bit(int nbits, int *addr)
{
   int i;
   for (i=0; i < nbits; i++)
      if (test_bit(i, addr) == 1)
         return i;
   return -EAGAIN;
} 

#endif
