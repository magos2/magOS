#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([elf-read], [0.01], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([elf_loader.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.14 -Wall -Werror])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX

# Checks for libraries.
# FIXME: Replace `main' with a function in `-ltest':
AC_CHECK_LIB([test], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile
                 test/Makefile])
AC_OUTPUT
