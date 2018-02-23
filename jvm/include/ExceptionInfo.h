#ifndef EXCEPTION_INFO_H
#define EXCEPTION_INFO_H
/* Copyright 2016 @AR
 * Description of .class jse6
 * https://docs.oracle.com/javase/specs/index.html
 */
#include <vector>
#include <fstream>
#include <string>
#include <memory> //unique_ptr

#include "Types.h"
#include "Serializable.h"

class ExceptionInfo : public Serializable
{
  public:   
    u2 startPc;
    u2 endPc;
    u2 handlerPc;
    u2 catchType;
    
    void dump();
    void load(std::ifstream&);
};







#endif
