/* Copyrigth 2016 @AR
 *
 * Main java code runner.
 *  - Each method is associated with a Frame
 *  - Program counter(PC) is relatif to the current method code.
 */
#include <iostream> //cout, hex, dec
#include <cstdlib>
#include <iomanip> //setw
#include <stack>
#include <memory> //unique_ptr
using namespace std;

#include "Interpreter.h"
#include "Types.h"
#include "InstructionSet.h"
#include "JavaClass.h"
#include "ObjectRef.h"
#include "Jvm.h"

Interpreter::Interpreter ()
{
  this->mainClass = NULL;
  this->mainMethod = NULL;
  this->currentFrame = NULL;
  this->pc = 0;
  this->ir = 0;
  this->depth = 0;
}

Interpreter::~Interpreter () {}

void
Interpreter::run (JavaClass* clazz)
{
  this->mainClass = clazz;
  this->mainMethod = clazz->main;
  if (!mainMethod) {
    perror("Main method not fount");
    exit(EXIT_FAILURE);
  }
  cout<<"Running Main method..."<<endl;
  Frame* mainFrame = new Frame (mainMethod, mainClass);
  currentMethod = mainMethod;
  currentClass = mainClass;
  currentFrame = mainFrame;
  pc = 0;
  runCurrent();
}

// Switch to the next Method
void
Interpreter::switch_to(Frame* nextFrame)
{
  // save the old frame on the stack
  Frame* callerFrame = currentFrame;
  callerFrame->returnAddress = pc;
  frames.push(callerFrame);
  //switch to called method/frame
  currentFrame = nextFrame;
  currentMethod = nextFrame->method;
  currentClass = nextFrame->clazz;
  pc = 0;
}

void
Interpreter::runCurrent()
{
  while (pc < currentMethod->code_attribute->code_length) {
    fetch();
    decode();
    execute();
  }
}

//fetch the next instruction to execute, and move pc forward.
void
Interpreter::fetch()
{ 
  int opCode;
  u1 * code = currentMethod->code_attribute->code;
  
  opCode = code[pc]; 
  ir = opCode;
  operandSize = InstructionSet::instance()->get_operand_size(opCode);
  if (operandSize == 1) 
    operand = code[pc+1];
  else if (operandSize == 2) {
    u1 operandByte1 = code[pc+1]; 
    u1 operandByte2 = code[pc+2];
    operand = (operandByte1 << 8) + operandByte2;
  }
  pc += 1 + operandSize;
}

void
Interpreter::decode()
{
}

void
Interpreter::execute()
{
  int i, n;
  u4 index;
  char* data;
  ObjectRef* objectRef;
  j_int_t value;
  
  cout<<InstructionSet::instance()->get_mnemonic(ir);
  
  switch (ir) {
  case ALOAD_0:
  case ALOAD_1:
  case ALOAD_2:
  case ALOAD_3:
    n = ir - ALOAD_0; /*local variable index to be loaded:0..3*/
    value = currentFrame->locals[n];
    currentFrame->operandStack.push(value);
    break;
  case ASTORE_0:
  case ASTORE_1:
  case ASTORE_2:
  case ASTORE_3:
    {
      n = ir - ASTORE_0;
      j_int_t ref = currentFrame->operandStack.pop();
      currentFrame->locals[n] = ref; 
    }
    break;
  case BIPUSH:
    currentFrame->operandStack.push(operand);
    cout<<" "<<operand;
    break;
  case DUP:
    value = currentFrame->operandStack.pop();
    currentFrame->operandStack.push(value);
    break;
  case ICONST_1:
    currentFrame->operandStack.push(1);
    break;
  case ILOAD_1:
    value = currentFrame->locals[1];
    currentFrame->operandStack.push(value);
    break;
  case INVOKEVIRTUAL:
  case INVOKESPECIAL: // TODO separate invoke virtual/special
    {
      // resolving method
      u4 methodRefIndex = operand;
      CONSTANT_Methodref_info* methodRef = (CONSTANT_Methodref_info *)(currentClass->get_cp_info(methodRefIndex));
      method_info* nextMethod = currentClass->resolve_method(methodRef);
      if (nextMethod == nullptr) { //see findMethod
        currentFrame->operandStack.pop(); // make stack clean
        return;
      }
      cout<<" #"<<methodRefIndex<<"  //"
          <<currentClass->get_class_name(methodRef->class_index)<<"."<<currentClass->get_method_name(nextMethod)<<"  ";
      JavaClass* nextClass = currentClass;//TODO
      Frame* nextFrame = new Frame(nextMethod, nextClass); // create new frame
      int nargs = nextMethod->countParameters();
      for (i=0; i<nargs; i++) {  // putting params on local stack
        j_int_t arg = currentFrame->operandStack.pop();
        nextFrame->locals[i+1] = arg;
      }  
      j_int_t ref = currentFrame->operandStack.pop(); // objectRef = this
      nextFrame->locals[0] = ref; // locals[0] = this
      switch_to(nextFrame);
      depth++;
    }
    break;
  case ISHL:
    {
      j_int_t arg2 = currentFrame->operandStack.pop();
      j_int_t arg1 = currentFrame->operandStack.pop();
      value = arg1 << arg2;
      currentFrame->operandStack.push(value);
    }
    break;
  case ISTORE_1:
    value = currentFrame->operandStack.pop();
    currentFrame->locals[1] = value;
    break;
  case LDC:
    index = operand;
    data = currentClass->get_cp_utf8(index);
    cout<<" #"<<index<<"\t//"<<data;
    currentFrame->operandStack.push((j_int_t)data);
    break;
  case NEW:
    {
      int nameIndex = operand;
      char* className = currentClass->get_class_name(nameIndex);
      cout<<" #"<<nameIndex<<"\t//"<<className;
      objectRef = new ObjectRef(nameIndex, className);
      objectRef->clazz = currentClass; //todo resolve the object class
      objectRef->initFields();
      currentFrame->operandStack.push((j_int_t)objectRef);
      Jvm::Runtime()->edenSpace->add(objectRef);
    }
    break;
  case PUTFIELD:
    {
      index = operand;
      field_info* fieldInfo = currentClass->resolveField(index);
      char *field_name = currentClass->get_field_name(index);
      cout<<" #"<<index<<"\t//"<<field_name;
      value = currentFrame->operandStack.pop();
      objectRef = (ObjectRef*)currentFrame->operandStack.pop();
      objectRef->putField(fieldInfo, value);
    }
    break;
  case IRETURN:
    value = currentFrame->operandStack.pop();
    delete currentFrame;
    //switch
    currentFrame = frames.pop();
    currentFrame->operandStack.push(value);
    currentMethod = currentFrame->method;
    currentClass = currentFrame->clazz;
    pc = currentFrame->returnAddress;
    depth--;
    break;
  case RETURN:
    delete currentFrame;
    if (frames.empty()) //main return
      j_exit();
    //switch
    currentFrame = frames.pop();
    currentMethod = currentFrame->method;
    currentClass = currentFrame->clazz;
    pc = currentFrame->returnAddress;
    depth--;
    break;
  case SIPUSH:
    currentFrame->operandStack.push(operand);
    cout<<" "<<value;
    break;
  default:
    cout<<" : not implemented!";
    exit(EXIT_FAILURE);
  }
  cout<<endl;
     
  /* stacks control
  if (currentFrame->locals.size() > currentMethod->code_attribute->max_locals){
    cout<<"local stack size "<<currentFrame->locals.size()<<" > "<<currentMethod->code_attribute->max_locals<<endl;
    exit(EXIT_FAILURE);
  }*/
  if (currentFrame->operandStack.size() > currentMethod->code_attribute->max_stack){
    cout<<"operand stack size "<<currentFrame->operandStack.size()<<" > "<<currentMethod->code_attribute->max_stack<<endl;
    exit(EXIT_FAILURE);
  }
  
  currentFrame->dump(depth);
}

void
invokeVirtual (method_info* method) {
  
}

void
Interpreter::j_exit()
{
  cout<<endl;
  Jvm::Runtime()->shutdown ();
}
















