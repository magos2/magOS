#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#include <string>
#include <vector>

#include "Types.h"

struct byte_code {
  int opCode;
  std::string mnemonic;
  int operandSize; //in bytes
};

/*Singleton*/
class InstructionSet
{
  public:
    static InstructionSet* Instance();
    std::string getMnemonic (int opCode);
    int getOperandSize (int opCode);
    bool isImmOprand (int opCode); // return true if opCode has immediate operand(not in constant pool)
    
  private:
    static InstructionSet* _instance;
    
    struct byte_code byteCodeTable[256];
    
    InstructionSet ();
};

#define   def(opCode, mnemonic, operandSize) {(opCode), (mnemonic), (operandSize)}

#define   AALOAD          0x32      // load onto the stack a reference from an array                                       
#define   AASTORE         0x53      // store into a reference in an array                                               
#define   ACONST_NULL     0x1       // push a null reference onto the stack                                               
#define   ALOAD           0x19      // 1: index   load a reference onto the stack from a local variable #index                                            
#define   ALOAD_0         0x2a                                                        
#define   ALOAD_1         0x2b      // load a reference onto the stack from local variable 1                                               
#define   ALOAD_2         0x2c      // load a reference onto the stack from local variable 2                                               
#define   ALOAD_3         0x2d      // load a reference onto the stack from local variable 3                                               
#define   ANEWARRAY       0xbd      // 2: indexbyte1, indexbyte2   create a new array of references of length count and component type identified by the class reference index (indexbyte1 << 8 + indexbyte2    in the constant pool                                        
#define   ARETURN         0xb0      // return a reference from a method                                               
#define   ARRAYLENGTH     0xbe      // get the length of an array                                               
#define   ASTORE          0x3a      // 1: index   store a reference into a local variable #index                                            
#define   ASTORE_0        0x4b      // store a reference into local variable 0                                               
#define   ASTORE_1        0x4c      // store a reference into local variable 1                                               
#define   ASTORE_2        0x4d      // store a reference into local variable 2                                               
#define   ASTORE_3        0x4e      // store a reference into local variable 3                                               
#define   ATHROW          0xbf      // throws an error or exception (notice that the rest of the stack is cleared, leaving only a reference to the Throwable                                              
#define   BALOAD          0x33      // load a byte or Boolean value from an array                                               
#define   BASTORE         0x54      // store a byte or Boolean value into an array                                               
#define   BIPUSH          0x10      // 1: byte   push a byte onto the stack as an integer value                                            
#define   BREAKPOINT      0xca      // reserved for breakpoints in Java debuggers; should not appear in any class file                                               
#define   CALOAD          0x34      // load a char from an array                                               
#define   CASTORE         0x55      // store a char into an array                                               
#define   DUP             0x59      //value → value, value    duplicate the value on top of the stack        
#define   DUP_X1          0x5a      //value2, value1 → value1, value2, value1    insert a copy of the top value into the stack two values from the top. value1 and value2 must not be of the type double or long.                
#define   DUP_X2          0x5b      //value3, value2, value1 → value1, value3, value2, value1    insert a copy of the top value into the stack two (if value2 is double or long it takes up the entry of value3, too    or three values (if value2 is neither double nor long    from the top        
#define   DUP2            0x5c      //{value2, value1} → {value2, value1}, {value2, value1}    duplicate top two stack words (two values, if value1 is not double nor long; a single value, if value1 is double or long)                
#define   CHECKCAST       0xc0      // 2: indexbyte1, indexbyte2   checks whether an objectref is of a certain type, the class reference of which is in the constant pool at index (indexbyte1 << 8 + indexbyte2                                           
#define   GETFIELD        0xb4      // 2: indexbyte1, indexbyte2   get a field value of an object objectref, where the field is identified by field reference in the constant pool index (indexbyte1 << 8 + indexbyte2                                           
#define   GETSTATIC       0xb2      // 2: indexbyte1, indexbyte2   get a static field value of a class, where the field is identified by field reference in the constant pool index (indexbyte1 << 8 + indexbyte2                                           
#define   GOTO            0xa7      // 2: branchbyte1, branchbyte2   goes to another instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   GOTO_W          0xc8      // 4: branchbyte1, branchbyte2, branchbyte3, branchbyte4   goes to another instruction at branchoffset (signed int constructed from unsigned bytes branchbyte1 << 24 + branchbyte2 << 16 + branchbyte3 << 8 + branchbyte4                                           
#define   I2B             0x91      // convert an int into a byte                                            
#define   I2C             0x92      // convert an int into a character                                            
#define   I2D             0x87      // convert an int into a double                                            
#define   I2F             0x86      // convert an int into a float                                            
#define   I2L             0x85      // convert an int into a long                                            
#define   I2S             0x93      // convert an int into a short                                            
#define   IADD            0x60      // add two ints                                               
#define   IALOAD          0x2e      // load an int from an array                                               
#define   IAND            0x7e      // perform a bitwise and on two integers                                               
#define   IASTORE         0x4f      // store an int into an array                                               
#define   ICONST_M1       0x2       // load the int value −1 onto the stack                                               
#define   ICONST_0        0x3       // load the int value 0 onto the stack                                               
#define   ICONST_1        0x4       // load the int value 1 onto the stack                                               
#define   ICONST_2        0x5       // load the int value 2 onto the stack                                               
#define   ICONST_3        0x6       // load the int value 3 onto the stack                                               
#define   ICONST_4        0x7       // load the int value 4 onto the stack                                               
#define   ICONST_5        0x8       // load the int value 5 onto the stack                                               
#define   IDIV            0x6c      // divide two integers                                               
#define   IF_ACMPEQ       0xa5      // 2: branchbyte1, branchbyte2   if references are equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IF_ACMPNE       0xa6      // 2: branchbyte1, branchbyte2   if references are not equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IF_ICMPEQ       0x9f      // 2: branchbyte1, branchbyte2   if ints are equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IF_ICMPGE       0xa2      // 2: branchbyte1, branchbyte2   if value1 is greater than or equal to value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IF_ICMPGT       0xa3      // 2: branchbyte1, branchbyte2   if value1 is greater than value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IF_ICMPLE       0xa4      // 2: branchbyte1, branchbyte2   if value1 is less than or equal to value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IF_ICMPLT       0xa1      // 2: branchbyte1, branchbyte2   if value1 is less than value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IF_ICMPNE       0xa0      // 2: branchbyte1, branchbyte2   if ints are not equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IFEQ            0x99      // 2: branchbyte1, branchbyte2   if value is 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IFGE            0x9c      // 2: branchbyte1, branchbyte2   if value is greater than or equal to 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IFGT            0x9d      // 2: branchbyte1, branchbyte2   if value is greater than 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IFLE            0x9e      // 2: branchbyte1, branchbyte2   if value is less than or equal to 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IFLT            0x9b      // 2: branchbyte1, branchbyte2   if value is less than 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IFNE            0x9a      // 2: branchbyte1, branchbyte2   if value is not 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                        
#define   IFNONNULL       0xc7      // 2: branchbyte1, branchbyte2   if value is not null, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IFNULL          0xc6      // 2: branchbyte1, branchbyte2   if value is null, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2                                           
#define   IINC            0x84      // 2: index, const   increment local variable #index by signed byte const                                            
#define   ILOAD           0x15      // 1: index   load an int value from a local variable #index                                            
#define   ILOAD_0         0x1a      // load an int value from local variable 0                                               
#define   ILOAD_1         0x1b      // load an int value from local variable 1                                               
#define   ILOAD_2         0x1c      // load an int value from local variable 2                                               
#define   ILOAD_3         0x1d      // load an int value from local variable 3                                               
#define   IMPDEP1         0xfe      // reserved for implementation-dependent operations within debuggers; should not appear in any class file                                               
#define   IMPDEP2         0xff      // reserved for implementation-dependent operations within debuggers; should not appear in any class file                                               
#define   IMUL            0x68      // multiply two integers                                               
#define   INEG            0x74      // negate int                                               
#define   INSTANCEOF      0xc1      // 2: indexbyte1, indexbyte2   determines if an object objectref is of a given type, identified by class reference index in constant pool (indexbyte1 << 8 + indexbyte2                                           
#define   INVOKEDYNAMIC   0xba      // 4: indexbyte1, indexbyte2, 0, 0   invokes a dynamic method and puts the result on the stack (might be void); the method is identified by method reference index in constant pool (indexbyte1 << 8 + indexbyte2                                           
#define   INVOKEINTERFACE 0xb9      // 4: indexbyte1, indexbyte2, count, 0   invokes an interface method on object objectref and puts the result on the stack (might be void); the interface method is identified by method reference index in constant pool (indexbyte1 << 8 + indexbyte2                                           
#define   INVOKESPECIAL   0xb7      // 2: indexbyte1, indexbyte2,    invoke instance method on object objectref and puts the result on the stack (might be void); the method is identified by method reference index in constant pool (indexbyte1 << 8 + indexbyte2                                              
#define   INVOKESTATIC    0xb8      // 2: indexbyte1, indexbyte2   invoke a static method and puts the result on the stack (might be void); the method is identified by method reference index in constant pool (indexbyte1 << 8 + indexbyte2                                           
#define   INVOKEVIRTUAL   0xb6      // 2: indexbyte1, indexbyte2   invoke virtual method on object objectref and puts the result on the stack (might be void); the method is identified by method reference index in constant pool (indexbyte1 << 8 + indexbyte2                                           
#define   IOR             0x80      // bitwise int or                                               
#define   IREM            0x70      // logical int remainder                                               
#define   IRETURN         0xac      // return an integer from a method                                               
#define   ISHL            0x78      // int shift left                                               
#define   ISHR            0x7a      // int arithmetic shift right                                               
#define   ISTORE          0x36      // 1: index   store int value into variable #index                                         
#define   ISTORE_0        0x3b      // store int value into variable 0                                               
#define   ISTORE_1        0x3c      // store int value into variable 1                                               
#define   ISTORE_2        0x3d      // store int value into variable 2                                               
#define   ISTORE_3        0x3e      // store int value into variable 3                                               
#define   ISUB            0x64      // int subtract                                               
#define   IUSHR           0x7c      // int logical shift right                                               
#define   IXOR            0x82      // int xor                                  
#define   LDC             0x12      // 1: index    → value    push a constant #index from a constant pool (String, int or float    onto the stack                 
#define   JSR             0xa8      // 2: branchbyte1, branchbyte2   jump to subroutine at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2    and place the return address on the stack                                        
#define   JSR_W           0xc9      // 4: branchbyte1, branchbyte2, branchbyte3, branchbyte4   jump to subroutine at branchoffset (signed int constructed from unsigned bytes branchbyte1 << 24 + branchbyte2 << 16 + branchbyte3 << 8 + branchbyte4    and place the return address on the stack                                        
#define   L2D             0x8a      // convert a long to a double                                               
#define   L2F             0x89      // convert a long to a float                                               
#define   L2I             0x88      // convert a long to a int                                               
#define   MONITORENTER    0xc2      // enter monitor for object ("grab the lock" – start of synchronized(    section                                          
#define   MONITOREXIT     0xc3      // exit monitor for object ("release the lock" – end of synchronized(    section                                          
#define   MULTIANEWARRAY  0xc5      // 3: indexbyte1, indexbyte2, dimensions   create a new array of dimensions dimensions with elements of type identified by class reference in constant pool index (indexbyte1 << 8 + indexbyte2); the sizes of each dimension is identified by count1, [count2, etc.]                                            
#define   NEW             0xbb      // 2: indexbyte1, indexbyte2   create new object of type identified by class reference in constant pool index (indexbyte1 << 8 + indexbyte2                                        
#define   NEWARRAY        0xbc      // 1: atype   create new array with count elements of primitive type identified by atype                                            
#define   NOP             0x0       // perform no operation                                               
#define   POP             0x57      // discard the top value on the stack                                               
#define   POP2            0x58      // discard the top two values on the stack (or one value, if it is a double or long                                              
#define   PUTFIELD        0xb5      // 2: indexbyte1, indexbyte2   set field to value in an object objectref, where the field is identified by a field reference index in constant pool (indexbyte1 << 8 + indexbyte2                                              
#define   PUTSTATIC       0xb3      // 2: indexbyte1, indexbyte2,   set static field to value in a class, where the field is identified by a field reference index in constant pool (indexbyte1 << 8 + indexbyte2                                              
#define   RET             0xa9      // 1: index   continue execution from address taken from a local variable #index (the asymmetry with jsr is intentional                                           
#define   RETURN          0xb1      // return void from method                                               
#define   SALOAD          0x35      // load short from array                                               
#define   SASTORE         0x56      // store short to array                                               
#define   SIPUSH          0x11      // 2: byte1, byte2   push a short onto the stack                                            
#define   SWAP            0x5f      // swaps two top words on the stack (note that value1 and value2 must not be double or long                                              
#endif

