#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <vector>
#include <string>

#include "JavaClass.h"
#include "InstructionSet.h"
#include "Types.h"
#include "JavaClass.h"

// Singleton
class Disassembler
{ 
  public:
    static Disassembler* instance ();
    void disassemble (JavaClass*);    // disassemle hole class
    void disassemble (const CodeAttribute*); // disassemle jvm instructions
    
  private:
    static Disassembler* instance_;
    
    Disassembler() {};
    ~Disassembler () {};
};


#endif