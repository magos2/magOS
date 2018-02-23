#ifndef _KLIBC_H
#define _KLIBC_H

char* memcpy(char *src, char *dst, int len);

void memset(char *adr, char val, int len);
void memsetw(short *adr, short val, int len);
void memsetd(long *adr, long val, int len);

int itoa(char *buf, int n, int base);
int utoa(char *buf, unsigned long n, int base);

int atoi(char *str);

int ctoi(char c);

#define is_digit(c)   (((c - '0') >= 0 && (c - '0') <= 9)?1:0)

#endif
