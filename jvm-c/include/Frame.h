#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <stack>
#include <cstdint>

#include "Types.h"
#include "JavaClass.h"

template <class T> class JStack : public vector<T> {
  public:
    T pop() {
      T elem = vector<T>::back();
      vector<T>::pop_back();
      return elem;
    };
    void push(T elem) {vector<T>::push_back(elem);}
    void reserve(int size) {vector<T>::reserve(size);}
    bool empty() {return vector<T>::empty();}
};

class Frame {
  public:
    intptr_t returnAddress;
    j_int_t* locals;       //local variables
    JStack<j_int_t> operandStack; //operand Stack
    method_info* method;    // method associated with this frame
    JavaClass*   clazz;
    
    Frame (method_info* method, JavaClass* clazz) { 
      this->method = method;
      this->clazz = clazz;
      locals = new j_int_t[method->code_attribute->max_locals];
      operandStack.reserve(method->code_attribute->max_stack);
    };
    
    ~Frame () {
      delete [] locals;
    };
    void dump(int depth); //dump the frame
};

#endif



