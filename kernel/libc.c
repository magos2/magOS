#include <stdarg.h>
#include <libc.h>

char * memcpy(char *src, char *dst, int len)
{
   __asm__ ("rep movsb "
            ::"S"(src), "D"(dst), "c"(len):);
   return dst;
}

void memset(char *adr, char val, int len)
{
   __asm__ ("rep stosb "::"D"(adr), "al"(val), "c"(len):);
}

void memsetw(short *adr, short val, int len)
{
   __asm__ ("rep stosw "::"D"(adr), "ax"(val), "c"(len):);
}

void memsetd(long *adr, long val, int len)
{
   __asm__ ("rep stosl "::"D"(adr), "a"(val), "c"(len):);
}

/*convert an integer <n> to ascii string*/
int itoa( char *buf, int n, int base)
{
   int mod, i=0, j=0;
   char c;
   
   do {
      mod = n%base;
      buf[i++] = (mod<10)?(mod+'0'):(mod-10+'a');
   } while (n/=base);
   
   buf[i--] = '\0';
   
   for (j=0; j<i; j++, i--) {
      c = buf[j];
      buf[j] = buf[i];
      buf[i] = c;
   }
   
   return 0;   
}

int atoi(char *str)
{
   char *tmp = str;
   int n=0, base, itmp;
   
   if ((*tmp++ == '0') && (*tmp++ == 'x'))
      base = 16;
   else {
      base = 10;
      tmp = str;
   }
   for (;*tmp; tmp++){
     itmp = (*tmp<='9')?(*tmp-'0'):(*tmp-'a'+10);
     n = n*base + itmp;
   } 
   
   return n;
}

int ctoi(char c)
{
  return (c - '0');
}

int utoa( char *buf, unsigned long n, int base)
{
   int mod, i=0, j=0;
   char c;
   
   do {
      mod = n%base;
      buf[i++] = (mod<10)?(mod+'0'):(mod-10+'a');
   } while (n/=base);
   
   buf[i--] = '\0';
   
   for (j=0; j<i; j++, i--) {
      c = buf[j];
      buf[j] = buf[i];
      buf[i] = c;
   }
   
   return 0;   
}


