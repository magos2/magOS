/* Little/Big endian conversion. snipped from forums.codeguru.com*/

#ifndef JVM_ENDIAN_H
#define JVM_ENDIAN_H

#include "Types.h"

#define swap_u1(n)  ;/*nothing*/
#define swap_u2(n)  n = (n>>8) | (n<<8);
#define swap_u4(n)  n =  (n>>24)               |\
                         ((n<<8) & 0x00FF0000) |\
                         ((n>>8) & 0x0000FF00) |\
                         (n<<24);

inline void swap16(u2& n)
{
    n = (n>>8) | 
         (n<<8);
}

inline void swap32(u4& n)
{
    n =  (n>>24) | 
         ((n<<8) & 0x00FF0000) |
         ((n>>8) & 0x0000FF00) |
         (n<<24);
}

// __int64 for MSVC, "long long" for gcc
inline void swap64(unsigned long long& x)
{
    x = (x>>56) | 
        ((x<<40) & 0x00FF000000000000) |
        ((x<<24) & 0x0000FF0000000000) |
        ((x<<8)  & 0x000000FF00000000) |
        ((x>>8)  & 0x00000000FF000000) |
        ((x>>24) & 0x0000000000FF0000) |
        ((x>>40) & 0x000000000000FF00) |
        (x<<56);
}

#endif