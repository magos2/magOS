#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stack>

#include "JavaClass.h"
#include "Types.h"
#include "Frame.h"

class Interpreter {
  public:
    intptr_t pc; //Programm Counter
    int ir;      //Instruction Register: contain opCode
    int operandSize;
    u4  operand; //operand = (operandByte1<<8+operandByte2)
    JStack<Frame*> frames; /*stack of calling frames*/
    Frame* currentFrame; //currentMethod frame
    method_info* currentMethod;
    JavaClass*  currentClass;
    JavaClass*  mainClass;
    method_info* mainMethod;
    int depth; // method depth from main, for debugging
    
    Interpreter();
    ~Interpreter();
    void run (JavaClass*);
    void switch_to(Frame* frame);
    void runCurrent();
    void fetch();
    void decode();
    void execute();
    void j_exit();

};



#endif