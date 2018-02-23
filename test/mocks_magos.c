/* mocks of hardware level functions
 */
#include <stdarg.h>
#include <stdio.h>
#include <kernel.h>

void printk (const char * format,...)
{
  char buf[256];
  va_list args;
  
  va_start (args, format);
  vsprintf (buf,format, args);
  va_end (args);
  printf(buf);
}

void panic (const char * format,...)
{
  char buf[256];
  va_list args;
  
  va_start (args, format);
  vsprintf (buf,format, args);
  va_end (args);
  printf("Kernel panic %s", buf);
  while(1);
}
