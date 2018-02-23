#ifndef FSTREAM_UTILS_H
#define FSTREAM_UTILS_H

#include <fstream>

#include "Types.h"
#include "JvmEndian.h"

inline void read_u2 (u2& buf, std::ifstream& inf)
{
  inf.read(reinterpret_cast<char*>(&buf), sizeof(buf));
  endian_swap16(buf);
}

inline void read_u4 (u4& buf, std::ifstream& inf)
{
  inf.read(reinterpret_cast<char*>(&buf), sizeof(buf));
  endian_swap32(buf);
}

#endif