#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <stack>
#include <cstdint>

#include "Types.h"
#include "JavaClass.h"
#include "OperandValue.h"

#define fill_space2(n) setw((n)*2)<<"" 

class Frame {
  public:
    intptr_t returnAddress;
    std::vector<j_int_t> locals;    //local variables
    std::vector<j_int_t>  operandStack; //operand Stack
    MethodInfo* method;  // method associated with this frame
    
    Frame (MethodInfo* method) 
    { 
      this->method = method;
      locals.resize(this->method->codeAttribute->maxLocals);
      operandStack.reserve(this->method->codeAttribute->maxStack);
    };
    ~Frame () {};
    void dump(int depth); //dump the frame
};

#endif



