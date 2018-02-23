#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stack>

#include "JavaClass.h"
#include "Types.h"
#include "Frame.h"

class Interpreter 
{
  public:
    intptr_t pc; //Programm Counter
    int ir; //Instruction Register
    int operandSize;
    u1 operandByte1, operandByte2; //operand = (byte1<<8+byte2)
    std::stack<Frame*> jstack;
    Frame* currentFrame; //currentMethod frame
    MethodInfo* currentMethod;
    JavaClass*  currentClass;
    
    JavaClass*  mainClass;
    MethodInfo* mainMethod;
    
    int depth; // method depth from main, for debugging
    
    
    Interpreter ();
    ~Interpreter ();
    void run (JavaClass*);
    void callMethod(MethodInfo* method, Frame* frame);
    void runCurrent();
    void fetch();
    void decode();
    void execute();
    void j_exit();

};



#endif