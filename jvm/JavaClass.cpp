/* Copyright 2016 @AR
 *
 * Description of .class jse6
 * https://docs.oracle.com/javase/specs/index.html
 */
#include <iostream> //cout, hex, dec
#include <fstream>
#include <cstdlib>
#include <iomanip> //setw
#include <typeinfo> //typeid get classname
#include <memory> //unique_ptr
using namespace std;

#include "JavaClass.h"
#include "JvmEndian.h"
#include "ConstantTag.h"
#include "FStreamUtils.h"
#include "Disassembler.h"
#include "AccessFlags.h"

JavaClass::JavaClass() 
{
  this->header = new HeaderInfo();
} 

JavaClass::~JavaClass() 
{
  delete header;
  delete &constantPool;
  delete &interfaces;
  delete &fields;
  delete &methods;
  delete &attributes;
} 

void
JavaClass::load(ifstream& inf)
{
  int i;
  ConstantInfo* constantInfo;
  u1 tag;
  
  this->header->load(inf);
  
  if (header->major != JAVA_SE_8) {
    cout<<"JSE not suppoted : found "<<header->major
		<<", expected "<<JAVA_SE_8<<endl;
    exit(EXIT_FAILURE);
  }
  
  read_u2(constantCount, inf); 
  
  //load constants pool
  constantPool.reserve(constantCount);
  constantPool.push_back(NULL);
  for (i=1; i<constantCount; i++) {
    constantInfo = new ConstantInfo(); // used only to load tag, then freed
    constantInfo->load(inf);
    tag = constantInfo->tag;
    delete constantInfo;
    switch (static_cast<int>(tag)) {
    case CONSTANT_Class :
      constantInfo = new ConstantClassInfo();
      break;
    case CONSTANT_Methodref :
      constantInfo = new MethodRefInfo();
      break;
    case CONSTANT_Fieldref :
      constantInfo = new FieldRefInfo();
      break;
    case CONSTANT_InterfaceMethodref:
      break;
    case CONSTANT_String :
      constantInfo = new ConstantStringInfo ();
      break;
    case CONSTANT_Integer :
      constantInfo = new ConstantIntegerInfo ();
      break;
    case CONSTANT_Float :
      cout<<"Not yet implemeted constant CONSTANT_Float"<<endl;
      break;
    case CONSTANT_Long :
      cout<<"Not yet implemeted constant CONSTANT_Long"<<endl;
      break;
    case CONSTANT_Double :
      cout<<"Not yet implemeted constant CONSTANT_Double"<<endl;
      break;
    case CONSTANT_NameAndType :
      constantInfo = new ConstantNameAndTypeInfo();
      break;
    case CONSTANT_Utf8 :
      constantInfo = new ConstantUtf8Info ();
      break;
    case CONSTANT_MethodHandle :
      cout<<"Not yet implemeted constant CONSTANT_MethodHandle"<<endl;
      break;
    case CONSTANT_MethodType :
      cout<<"Not yet implemeted constant CONSTANT_MethodType"<<endl;
      break;
    case CONSTANT_InvokeDynamic :
      constantInfo = new ConstantInvokeDynamicInfo();
      break;
    default :
      cout<<"Unknown constant tag: "<<static_cast<int>(tag)<<endl;
      break;
    };
    constantInfo->tag = tag;
    constantInfo->load(inf);
    constantPool.push_back(constantInfo);
  }
  
  read_u2(accessFlags, inf);
  read_u2(thisClass, inf);
  read_u2(superClass, inf);
 
  //Interfaces 
  read_u2(interfaceCount, inf); 
  interfaces.reserve(interfaceCount);
  for (i=0; i<interfaceCount; i++)
    inf.read(reinterpret_cast<char*>(&interfaces[i]), sizeof(u2)); 
    
  //Fields 
  read_u2(fieldCount, inf); 
  fields.reserve(fieldCount);
  for (i=0; i<fieldCount; i++) {
    FieldInfo* field = new FieldInfo (this);
    field->load(inf);
    fields.push_back (field);
  }
    
  //Methods
  read_u2(methodCount, inf); 
  methods.reserve(methodCount);
  for (i=0; i<methodCount; i++) {
    MethodInfo* method = new MethodInfo (this);
    method->load(inf);
    methods.push_back(method);
  }
}

void
JavaClass::dump()
{
  int i;
  
  this->header->dump();
  
  cout<<hex<<showbase;
  cout<<"access Flags: "<<access_flag_lebel(accessFlags)<<endl;
  cout<<"thisClass: "<<thisClass<<endl;
  cout<<"superClass: "<<superClass<<endl;
  
  //constants pool
  cout<<left;
  cout<<setw(20)<<"Counstant Count: "<<dec<<constantCount<<endl;
  cout<<"Constant Pool:"<<endl;
  for (i=1; i<constantCount; i++) {
    cout<<"\t"<<"#"<<dec<<i<<" = ";
    constantPool.at(i)->dump();
    cout<<"// "<<*constantPool.at(i)->getValue(this->constantPool).get()<<endl;
  }
    
  //dump interfaces
  cout<<"Interfaces Count: "<<dec<<interfaceCount<<endl;
  for (i=0; i<interfaceCount; i++)
    cout<<"Interface: "<<interfaces[i]<<endl;
    
  //dump Fields 
  cout<<"Fields Count: "<<dec<<fieldCount<<endl;
  for (FieldInfo* field : this->fields) 
    field->dump();
    
  //dump Methods 
  cout<<"Methods Count: "<<dec<<methodCount<<endl;
  for (MethodInfo* method : this->methods) 
    method->dump();
}

void
HeaderInfo::load(ifstream& inf)
{
  read_u4(magic, inf);
  read_u2(minor, inf);
  read_u2(major, inf);
}

void
HeaderInfo::dump()
{
  cout<<"Header Info:"<<endl;
  cout<<setw(10)<<"magic: "<<hex<<showbase<<magic<<endl;
  cout<<setw(10)<<"minor: "<<hex<<showbase<<minor<<endl;
  cout<<setw(10)<<"major: "<<hex<<showbase<<major<<endl;
}

unique_ptr<string> 
JavaClass::getName ()
{
  return this->getConstantValue (thisClass);
}

size_t
JavaClass::size ()
{
  size_t siz = sizeof (this);
  siz += constantCount * sizeof (constantPool);
  siz += fieldCount * sizeof (fields);
  siz += methodCount * sizeof (methods);
  siz += attributesCount * sizeof (attributes);
  return siz;
}

ConstantInfo* 
JavaClass::getConstantInfo(int index)
{
  return this->constantPool[index];
}

unique_ptr<string>
JavaClass::getConstantValue(int index)
{
  return this->constantPool[index]->getValue(this->constantPool);
}

MethodInfo* 
JavaClass::findMethod (MethodRefInfo* methodRef)
{
  if (methodRef->classIndex != this->thisClass) {
     cout <<"Error : cannot yet search in class #"<<dec<<methodRef->classIndex<<endl;
     return nullptr;
  }
  
  ConstantNameAndTypeInfo* nameAndType = dynamic_cast<ConstantNameAndTypeInfo*>(this->constantPool[methodRef->nameAndTypeIndex]);
  for (MethodInfo* method : this->methods)
    if (method->nameIndex == nameAndType->nameIndex &&
        method->descriptorIndex == nameAndType->descriptorIndex)
       return method;
  
  string msg_error = "Error : No method found for index #" + to_string(methodRef->nameAndTypeIndex);
  perror (msg_error.c_str());
  exit (EXIT_FAILURE); 
}

FieldInfo*
JavaClass::resolveField (u4 index)
{
  FieldRefInfo* fieldRef = dynamic_cast<FieldRefInfo*>(getConstantInfo (index));
  ConstantNameAndTypeInfo* nameAndType = dynamic_cast<ConstantNameAndTypeInfo*>(getConstantInfo (fieldRef->nameAndTypeIndex));
  for (FieldInfo* fieldInfo : this->fields)
    if (fieldInfo->nameIndex == nameAndType->nameIndex && fieldInfo->descriptorIndex == nameAndType->descriptorIndex)
      return fieldInfo;
  return nullptr;
}

