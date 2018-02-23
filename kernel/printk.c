#include <stdarg.h>
#include "console.h"
#include "kernel.h"
 
void printk(const char * format,...)
{
  char buf[512];
  va_list args;
  
  va_start (args, format);
  
  vsprintf (buf,format, args);
  
  cons_write (buf);
  
  va_end (args);
}

