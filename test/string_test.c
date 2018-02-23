#include "string.h"
#include <stdio.h>

void strcpy_test()
{
   char * s1 = "abc12";
   char  s2[10] = {'t','s','3'};
   printf("strcpy test : s1=<%s>, s2=<%s> avant.", s1 , s2); 
   char * s3 = strcpy(s1, s2);
   printf(" apres : s1=<%s>, s2=<%s>, s3=<%s>\n", s1 , s2, s3); 
}


void strlen_test()
{
   char * s1 = "abcd1234";
   int n = strlen(s1);
   printf("Size of <%s>: %d\n", s1 , n); 
}

void strcat_test()
{
   char s1[20] = "salamo ";
   char * s2 = "alikom";
   printf("strcpy test : s1=<%s>, s2=<%s> avant.", s1 , s2); 
   char * s3 = strcat(s1, s2);
   printf(" apres : s1=<%s>, s2=<%s>, s3=<%s>\n", s1 , s2, s3); 
}

int main(int argv, char **args)
{
   strlen_test();

   strcpy_test();

   strcat_test();
   
   return 0;
}
