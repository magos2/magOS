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

#include "AttributeInfo.h"
#include "JavaClass.h"
#include "JvmEndian.h"
#include "ConstantTag.h"
#include "FStreamUtils.h"
#include "Disassembler.h"
#include "AccessFlags.h"


void
AttributeInfo::loadHead(ifstream& inf)
{
  read_u2(attributeNameIndex, inf);
  read_u4(attributeLength, inf);
}
void
AttributeInfo::loadInfo(ifstream& inf)
{
  info.reserve(attributeLength);
  inf.read(&info[0], attributeLength); 
}

void
AttributeInfo::load(ifstream& inf)
{
  this->loadHead(inf);
  this->loadInfo(inf);
}

void
AttributeInfo::dump()
{
  cout<<"\t"<<"Attribute Info:"<<endl;
  cout<<"\t\t"<<"attributeNameIndex: "<<dec<<attributeNameIndex<<endl;
  cout<<"\t\t"<<"attributeLength: "<<attributeLength<<endl;
  cout<<"\t\t"<<"info: "<<info.data()<<endl;
}

void
CodeAttribute::load(ifstream& inf)
{
  int i;
  
  loadHead(inf);
  read_u2(maxStack, inf);
  read_u2(maxLocals, inf);
  
  read_u4(codeLength, inf);
  code.resize(codeLength);
  inf.read(&code[0], codeLength); 
  
  read_u2(exceptionTableLength, inf);
  exceptionTable.reserve(exceptionTableLength);
  for (i=0; i<exceptionTableLength; i++) {
     ExceptionInfo* exception = new ExceptionInfo();
     exception->load(inf);
     exceptionTable.push_back (exception);
  }
  
  read_u2(attributesCount, inf);
  attributes.reserve(attributesCount);
  for (i=0; i<attributesCount; i++) {
     AttributeInfo* attribute = new AttributeInfo();
     attribute->load(inf);
     attributes.push_back (attribute);
  }
}

void
CodeAttribute::dump()
{
  cout<<dec;
  cout<<"\t"<<"Code:"<<endl;
  Disassembler::instance()->disassemble(this);
  cout<<dec<<endl;
  
  cout<<"\t"<<"exceptionTableLength: "<<exceptionTableLength<<endl;
  for (ExceptionInfo* exception : this->exceptionTable)
    exception->dump();
    
  cout<<"\t"<<"attributesCount: "<<attributesCount<<endl;
  for (AttributeInfo* attribute : this->attributes)
    attribute->dump();
}
