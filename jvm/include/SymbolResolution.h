/* Copyright 2016 @AR
 *
 * p.5.4.3 Implementaion of the JVM 8 Spec
 */
#ifndef SYMBOL_RESOLUTION_H
#define SYMBOL_RESOLUTION_H

#include "Types.h"

//Resolution of symbolic references
class SymbolResolution
{
  public:
    j_int_t Interpreter::resolveSymbol (u4 index);
};




#endif



