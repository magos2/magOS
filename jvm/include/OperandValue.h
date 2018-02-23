#ifndef OPERAND_VALUE
#define OPERAND_VALUE

#include <string>

struct operand_value {
  public:
    enum {INT=1, FLOAT=2, OBJECTREF=3} tag;
    union { 
      int int_v;
      float float_v;
      intptr_t objectref;
    };
    
    operand_value () {};
    operand_value (int value) { tag = INT; int_v = value;};
    operand_value (float value) { tag = FLOAT; float_v = value;};
 
};

class OperandValue {
  
};

class OperandValueString {
  public:
    string value;
    OperandValueString (std::string s) {value = s;}
    ~OperandValueString(){};
};






#endif