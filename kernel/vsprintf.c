#include <stdarg.h>
#include "kernel.h"
#include "string.h"
#include "libc.h"

int tab_size = 4; /*4 spaces*/

int vsprintf (char *buf, const char * format, va_list args )
{
   char c;
   int i, j, k;
   unsigned long n;
   char nbstr[80]; /*for nb to string conversion*/
   char *str;
   int x_prefix = 0; /*if 1, add 0x prefix*/
   int width = 0;
   
   i = 0;
   do {
      if (*format == '%') {
         format++;
         width = 0;
         j = 0;
         while (is_digit(*format)) 
           nbstr[j++] = *format++;
         nbstr[j] = '\0';
         if (j > 0)
           width = atoi(nbstr);
         switch (*format) {
            case 'c': c = va_arg(args, int);
                      buf[i++] = c;
                      break;
            case 'd': n = va_arg(args, int);
                      itoa(nbstr , n, 10);
                      j=0;
                      while (nbstr[j])
                         buf[i++] = nbstr[j++];
                      for (k=j; k < width; k++)
                        buf[i++] = ' ';
                      break; 
            case '#': x_prefix = 1; //add 0x prefix
                      format++; 
                      //continue to next, dont break
            case 'x': n = va_arg(args, unsigned long);
                      utoa(nbstr , n, 16);
                      if (x_prefix) {
                        buf[i++] = '0';
                        buf[i++] = 'x';
                        x_prefix = 0;
                      }
                      for(k=0; k<(width - strlen(nbstr)); k++)
                        buf[i++]='0';
                      j=0;
                      while (nbstr[j])
                         buf[i++] = nbstr[j++];
                      for (k=j; k < width; k++)
                        buf[i++] = ' ';
                      break;
            case 's': str = va_arg(args, char *);
                      for (j=0; *str; str++, j++)
                         buf[i++] = *str;
                      for (k=j; k < width; k++)
                        buf[i++] = ' ';
                      break;
            default : buf[i++] = '%'; 
                      buf[i++] = *format;
                      break;
         }
      }
      else if (*format == '\t')
         for (j=0; j<tab_size;j++)
           buf[i++] = ' ';
      else
         buf[i++] = *format;
   } while(*format++);
   
   buf[i] = '\0';
   
   return 0;
}


