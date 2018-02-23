/* Copyright 2016 @AR
 *
 * This is a mini shell
 */
#include <types.h>
#include <unistd.h>
#include <string.h>

#define NB_OPTS 10   /*max number of options of a user command*/
#define new_line()  printf("\n")


void printf (char* s)
{
  console_write (s);
}

void scanf (char* buf)
{
  console_read (buf);
}

#define DEF_CMD0(fn) void _##fn() {          \
                       pid_t pid = fork();   \
                       if (pid == 0){        \
                        fn();                \
                        exit();              \
                       } else                \
                           wait();           \
                     }

#define DEF_CMD1(fn,arg1) void _##fn(char* arg1) {  \
                            pid_t pid = fork();     \
                            if (pid == 0){          \
                              fn(arg1);             \
                              exit();               \
                            } else                  \
                                wait();             \
                          }



DEF_CMD0(ls)
DEF_CMD0(pwd)
DEF_CMD1(cd, pathname)
DEF_CMD0(ps)
DEF_CMD0(free)
DEF_CMD0(clear)

int main(void) {
  char buf[128];
  char* ps1 = "# ";
  char* cmd;
  char* argv[NB_OPTS];
  int nargs;
  char *p;
  
  for (;;) {
    printf (ps1);
    scanf(buf);
    new_line();
    /*- parsing arguments -*/;
    nargs = 0;
    cmd = argv[0] = p = &buf[0];
    for (; *p != '\0' && nargs < NB_OPTS; p++) {
     if (*p == ' ') {
       *p = '\0'; p++; /*end of an arg*/
       while (*p == ' ') p++;
       if (*p != '\0') {
         nargs++;
         argv[nargs] = p;
       }
      }
    }
    /*--*/
    
    /*ls*/
    if (strcmp(cmd, "ls") == 0)
      _ls();
    /*cd*/
    else if (strcmp(cmd, "cd") == 0) {
      if (nargs == 0)
        _cd("/");
      else
        _cd(argv[1]);
    }
    /*pwd*/
    else if (strcmp(cmd, "pwd") == 0)
      _pwd();
    /*ps*/
    else if (strcmp(cmd, "ps") == 0)
      _ps();
    /*free*/
    else if (strcmp(cmd, "free") == 0)
      _free();
    /*free*/
    else if (strcmp(cmd, "clear") == 0)
      _clear();
    /*help*/
    else if (strcmp(cmd, "help") == 0 || strcmp(cmd, "?") == 0)
      printf ("Shell Help!\n");
    else if (strcmp(cmd, "") == 0)
      ;//do nothing
    else
      printf ("command not found\n");
  }
  return 0;
}
