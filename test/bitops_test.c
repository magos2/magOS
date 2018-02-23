#include <stdio.h>
#include <assert.h>
#include "bitops.h"

void set_bit_test()
{
   printf("Testing set_bit_test...");   

   int a[3] = {0x1f3, 0xc0000000, 0xffff1111};

   set_bit(2, (int *)&a);
   assert(a[0] == 0x1f7);

   set_bit(56, (int *)&a);
   assert(a[1] == 0xc1000000);
   
   printf("[OK]\n");   
} 

void clear_bit_test()
{
   printf("Testing clear_bit_test...");   

   int a[3] = {0x1f3, 0xc0000000, 0xf1ff1111};

   clear_bit(1, (int *)&a);
   assert(a[0] == 0x1f1);

   clear_bit(88, (int *)&a);
   assert(a[2] == 0xf0ff1111);
   
   printf("[OK]\n");   
}

void find_first_zero_bit_test()
{
   int bit;
   int a[3] = {0xffffffff, 0xc0000003, 0xf1ff1111};

   printf("Testing find_first_zero_bit...");   

   bit = find_first_zero_bit(sizeof(a)*32, a);
   assert( bit == 34);
 
   printf("[OK]\n");   
}

void find_first_bit_test()
{
   int bit;
   int a[3] = {0x80000000, 0x00000100, 0xf1fff000};

   printf("Testing find_first_bit...");   

   bit = find_first_bit(sizeof(a)*32, a);
   assert( bit == 31);

   printf("[OK]\n");   
}

int main(int argv, char **args)
{
   set_bit_test();
   clear_bit_test();

   find_first_zero_bit_test();

   find_first_bit_test();

   return 0;
}
