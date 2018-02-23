#ifndef MAGOS_UNISTD_H
#define MAGOS_UNISTD_H

#define SYS_restart       0
#define SYS_exit          1
#define SYS_fork          2
#define SYS_execv         3
#define SYS_console_write 4
#define SYS_console_read  5
#define SYS_uname         6
#define SYS_setup         7
#define SYS_wait          8
#define SYS_wakeup        9
#define SYS_ls           10
#define SYS_cd           11
#define SYS_pwd          12
#define SYS_ps           13
#define SYS_free         14
#define SYS_clear        15

static inline int syscall0(int sys_num) __attribute__((always_inline));
static inline int syscall1(int sys_num, char* arg1) __attribute__((always_inline));

static inline int syscall0(int sys_num)
{
  int retval;
  __asm__ ("int $0x80      \n\t"
           "mov %%eax, %0":"=m"(retval):"a"(sys_num):"memory");
  return retval;
}

static inline int syscall1(int sys_num, char* arg1)
{
  int retval;
  __asm__("int $0x80      \n\t"
          "mov %%eax, %0":"=m"(retval):"a"(sys_num),"b"(arg1):"memory");
  return retval;
}

#define DEF_SYSCALL0(type, fn)                                    \
  static inline type fn() __attribute__((always_inline));         \
  static inline type fn() {                                       \
    int retval;                                                   \
    __asm__ ("int $0x80      \n\t"                                \
             "mov %%eax, %0":"=m"(retval):"a"(SYS_##fn):"memory");\
    return retval;                                                \
  }

#define DEF_SYSCALL1(type, fn, arg1)                                        \
  static inline type fn(char* arg1) __attribute__((always_inline));         \
  static inline type fn(char* arg1) {                                       \
    int retval;                                                             \
    __asm__ ("int $0x80      \n\t"                                          \
             "mov %%eax, %0":"=m"(retval):"a"(SYS_##fn),"b"(arg1):"memory");\
    return retval;                                                          \
  }
  
DEF_SYSCALL0 (int, exit);
DEF_SYSCALL0 (int, fork);
DEF_SYSCALL1 (int, execv, filename);
DEF_SYSCALL1 (int, console_write, s);
DEF_SYSCALL1 (int, console_read, buf);
DEF_SYSCALL0 (int, wait);
DEF_SYSCALL0 (int, ls);
DEF_SYSCALL1 (int, cd, pathname);
DEF_SYSCALL0 (int, pwd);
DEF_SYSCALL0 (int, ps);
DEF_SYSCALL0 (int, free);
DEF_SYSCALL0 (int, clear);


#endif