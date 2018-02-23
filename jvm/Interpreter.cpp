/* Copyrigth 2016 @AR
 *
 * Main java code runner
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
#include "ConstantInfo.h"
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
  //searching main method in methos vector
  for (MethodInfo* method : clazz->methods) {
    u2 nameIndex = method->nameIndex;
    ConstantUtf8Info* nameUtf8 = dynamic_cast<ConstantUtf8Info*>(clazz->constantPool[nameIndex]);
    if (string(nameUtf8->bytes.data()) == "main") {
      this->mainClass = clazz;
      this->mainMethod = method;
      break;
    }
  }
  
  if (!mainMethod) {
    perror("Main method not fount");
    exit(EXIT_FAILURE);
  }
  cout<<"Running Main method..."<<endl;
  Frame* mainFrame = new Frame (mainMethod);
  currentMethod = mainMethod;
  currentClass = mainClass;
  currentFrame = mainFrame;
  pc = 0;
  runCurrent();
}

// Switch to the current Method
void
Interpreter::callMethod(MethodInfo* method, Frame* frame)
{
  // save the old frame on the stack
  Frame* callerFrame = currentFrame;
  callerFrame->returnAddress = pc;
  jstack.push(callerFrame);
  
  currentMethod = method;
  currentClass = method->clazz;
  currentFrame = frame;
  pc = 0;
}

void
Interpreter::runCurrent()
{
  while (pc < static_cast<intptr_t>(currentMethod->codeAttribute->codeLength)) {
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
  const vector<u1>& code = currentMethod->codeAttribute->code;
  
  opCode = static_cast<int>(code[pc++]); 
  ir = opCode;
  operandSize = InstructionSet::Instance()->getOperandSize(opCode);
    
  if (operandSize == 1) 
    operandByte1 = code[pc];
  
  else if (operandSize == 2) {
    operandByte1 = code[pc]; 
    operandByte2 = code[pc + 1];
  }
  pc += operandSize;
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
  struct operand_value operandValue;
  unique_ptr<string> data;
  ObjectRef* objectRef;
  j_int_t value;
  
  cout<<fill_space2(depth)<<InstructionSet::Instance()->getMnemonic(ir);
  
  switch (ir) {
  case ALOAD_0:
  case ALOAD_1:
  case ALOAD_2:
  case ALOAD_3:
    n = ir - ALOAD_0;
    value = currentFrame->locals[n];
    currentFrame->operandStack.push_back(value);
    break;
  case ASTORE_0:
  case ASTORE_1:
  case ASTORE_2:
  case ASTORE_3:
    {
      n = ir - ASTORE_0;
      j_int_t ref = currentFrame->operandStack.back ();
      currentFrame->operandStack.pop_back ();
      currentFrame->locals[n] = ref; 
    }
    break;
  case BIPUSH:
    currentFrame->operandStack.push_back(j_cast(operandByte1));
    cout<<" "<<dec<<j_cast(operandByte1);
    break;
  case DUP:
    value = currentFrame->operandStack.back();
    currentFrame->operandStack.push_back(value);
    break;
  case ICONST_1:
    currentFrame->operandStack.push_back(1);
    break;
  case ILOAD_1:
    value = currentFrame->locals[1];
    currentFrame->operandStack.push_back(value);
    break;
  case INVOKEVIRTUAL:
  case INVOKESPECIAL: // todo separate invoke virtual/special
    {
      // resolving method
      u4 methodRefIndex = (operandByte1 << 8) + operandByte2;
      MethodRefInfo* methodRef = dynamic_cast<MethodRefInfo*>(currentClass->constantPool[methodRefIndex]);
      cout<<" #"<<dec<<methodRefIndex
          <<"\t// "<<*methodRef->getValue(currentClass->constantPool)<<"  ";
      MethodInfo* nextMethod = currentClass->findMethod (methodRef);
      if (nextMethod == nullptr) { //see findMethod
        currentFrame->operandStack.pop_back (); // make stack clean
        return;
      }
    
      Frame* nextFrame = new Frame (nextMethod); // create new frame
      int nargs = nextMethod->countParameters ();
      nextFrame->locals.resize(nargs+1);
      for (i=0; i<nargs; i++) {  // putting params on local stack
        j_int_t arg = currentFrame->operandStack.back ();
        currentFrame->operandStack.pop_back ();
        nextFrame->locals[i+1] = arg;
      }  
      j_int_t ref = currentFrame->operandStack.back (); // objectRef = this
      currentFrame->operandStack.pop_back ();
      nextFrame->locals[0] = ref; // locals[0] = this
    
      callMethod (nextMethod, nextFrame);
      depth++;
    }
    break;
  case ISHL:
    {
      j_int_t arg2 = currentFrame->operandStack.back();
      currentFrame->operandStack.pop_back ();
      j_int_t arg1 = currentFrame->operandStack.back();
      currentFrame->operandStack.pop_back ();
      value = arg1 << arg2;
      currentFrame->operandStack.push_back(value);
    }
    break;
  case ISTORE_1:
    value = currentFrame->operandStack.back();
    currentFrame->operandStack.pop_back ();
    currentFrame->locals[1] = value;
    break;
  case LDC:
    index = operandByte1;
    data = currentClass->getConstantValue(index);
    cout<<" #"<<index<<"\t//"<<*data;
    currentFrame->operandStack.push_back(reinterpret_cast<j_int_t>((*data).c_str()));
    break;
  case NEW:
    {
      int nameIndex = (operandByte1 << 8) + operandByte2;
      unique_ptr<string> className = currentClass->getConstantValue(nameIndex);
      cout<<" #"<<nameIndex<<"\t//"<<*className;
      objectRef = new ObjectRef (nameIndex, *className);
      objectRef->clazz = currentClass; //todo resolve the object class
      objectRef->initFields ();
      currentFrame->operandStack.push_back(reinterpret_cast<j_int_t>(objectRef));
      Jvm::Runtime()->edenSpace->add (objectRef);
    }
    break;
  case PUTFIELD:
    {
      index = (operandByte1 <<8) | operandByte2;
      FieldInfo* fieldInfo = currentClass->resolveField(index);
      data = currentClass->getConstantValue(index);
      cout<<" #"<<index<<"\t//"<<*data;
      value = currentFrame->operandStack.back();
      currentFrame->operandStack.pop_back();
      objectRef = reinterpret_cast<ObjectRef*>(currentFrame->operandStack.back());
      currentFrame->operandStack.pop_back();
      objectRef->putField (fieldInfo, value);
    }
    break;
  case IRETURN:
    value = currentFrame->operandStack.back();
    delete currentFrame;
    //switch
    currentFrame = jstack.top ();
    jstack.pop ();
    currentFrame->operandStack.push_back(value);
    currentMethod = currentFrame->method;
    currentClass = currentMethod->clazz;
    pc = currentFrame->returnAddress;
    depth--;
    break;
  case RETURN:
    delete currentFrame;
    if (jstack.empty()) //main return
      j_exit();
      
    //switch
    currentFrame = jstack.top ();
    jstack.pop ();
    currentMethod = currentFrame->method;
    currentClass = currentMethod->clazz;
    pc = currentFrame->returnAddress;
    depth--;
    break;
  case SIPUSH:
    value = (operandByte1 << 8) | operandByte2;
    currentFrame->operandStack.push_back(j_cast(value));
    cout<<" "<<dec<<value;
    break;
  default:
    cout<<" : not implemented!";
    break;
  }
  cout<<endl;
     
  // stacks control
  if (currentFrame->locals.size() > currentMethod->codeAttribute->maxLocals){
    cout<<"local stack size "<<currentFrame->locals.size()<<" > "<<currentMethod->codeAttribute->maxLocals<<endl;
    exit(EXIT_FAILURE);
  }
  if (currentFrame->operandStack.size() > currentMethod->codeAttribute->maxStack){
    cout<<"operand stack size "<<currentFrame->operandStack.size()<<" > "<<currentMethod->codeAttribute->maxStack<<endl;
    exit(EXIT_FAILURE);
  }
  
  currentFrame->dump(depth);
}

void
invokeVirtual (MethodInfo* method) {
  
}

void
Interpreter::j_exit ()
{
  cout<<endl;
  Jvm::Runtime()->shutdown ();
}
















