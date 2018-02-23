#ifndef MAGOS_STDDEF_H
#define MAGOS_STDDEF_H

#undef NULL
#define NULL ((void *)0)

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif


#undef offsetof
#define offsetof(type, fieldname) ((size_t) &((type *)0)->fieldname)


#endif