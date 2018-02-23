/*
 * gcc divers.c -o /usr/local/bin/divers
 */
#include <stdio.h>

#define NR_HASH 10

#define hash_func(dev, blocknr) ((dev^blocknr) % NR_HASH)

void test_hash ()
{
  int dev, block;
  for (dev=0; dev<=3; dev++)
  for (block=0; block <= 15; block++)
    printf ("hash dev=%d block=%d : %d\n", dev, block, hash_func(dev, block));
  
}

void test_while (int nr) {
  while(nr-->0)
    printf("%d\n", nr);
}

/*Algorithm:
  IN                     OUT
  path=/usr/local        buf=/, return=usr/local 
  path=usr/local         buf=usr, return=local 
  path=local             buf=local, return=NULL
 */
char* path_walk(char *path, char* buf)
{
  char *pathp = path;
  char *bufp  = buf;
  while (*pathp == '/') pathp++; /*skipe next slashes: /////local*/
  for (; *pathp != '/' && *pathp != '\0'; pathp++, bufp++)
    *bufp = *pathp;
  *bufp = '\0';
  return pathp;         
}


int main(void) {
  //test_hash();
  //test_while(3);
  /////path walk/////
  char *path = "/usr/./..///local/";
  char buf[64];
  int i;
  printf ("initial path=%s\n", path);
  for (i=0; i < 6; i++) {
    path = path_walk(path, &buf[0]);
    printf ("dirname=%s, next path=%s\n", &buf[0], path);
  }
  /////
  
}




