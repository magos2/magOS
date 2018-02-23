#include <stdio.h>
 
extern int my_glob;
int ml_func(int);

int main ()
{
  ml_func (3);
  printf ("my_glob = %d\n", my_glob);
  return 0;
}
  