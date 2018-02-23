/*
 * Notes :
 *   - a page is splited into blocks with same size.
 *   - buffer_head is located in front of evry free block.
 */
#include <stdio.h>
#include <stdlib.h>
#include <list.h>

#define MAX_ORDER 8

struct buffer_head { /*in front of evry free bloc*/
  int size;
  struct list_head list;
};


struct size_desc {
  int size;
  struct list_head freelist; /*list of buffer heads*/
};


struct size_desc malloc_sizes[MAX_ORDER+1] = /*min 32 bytes, max 4k bytes*/
                     {{32,   {}},
                      {64,   {}},
                      {128,  {}},
                      {256,  {}},
                      {512,  {}},
                      {1024, {}},
                      {2048, {}},
                      {4096, {}},
                      {0,    {}} };
                   


int main(void)
{
  return 0;
}




                   
         
                     