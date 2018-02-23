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

#include "ConstantInfo.h"
#include "JavaClass.h"
#include "JvmEndian.h"
#include "ConstantTag.h"
#include "FStreamUtils.h"
#include "Disassembler.h"
#include "AccessFlags.h"



void
ConstantInfo::load(ifstream& inf)
{
  inf.read(&tag, sizeof(tag));  
}

unique_ptr<string>
ConstantInfo::getValue(vector<ConstantInfo*>  const& constantPool)
{
  unique_ptr<string> s(new string("Must be implemented by the derivied class!"));
  return s;
}

void
ConstantInfo::dump()
{
  cout<<"Constant Info:"<<endl;
  cout<<setw(10)<<"tag: "<<static_cast<int>(tag)<<endl;
}

void
ConstantClassInfo::load(ifstream& inf)
{
  read_u2(nameIndex, inf);
}

void
ConstantClassInfo::dump()
{
  cout<<setw(20)<<"Class"
      <<setw(15)<<"#"+to_string(nameIndex);
}

unique_ptr<string>
ConstantClassInfo::getValue(vector<ConstantInfo*>  const& constantPool)
{
  return constantPool[nameIndex]->getValue(constantPool);
}

void
ConstantRefInfo::load(ifstream& inf)
{
  read_u2(classIndex, inf);
  read_u2(nameAndTypeIndex, inf); 
}

void
ConstantRefInfo::dump()
{
  if (static_cast<int>(tag) == CONSTANT_Fieldref)
    cout<<setw(20)<<"FieldRef";
  else if (static_cast<int>(tag) == CONSTANT_Methodref)
    cout<<setw(20)<<"MethodRef";
  else if (static_cast<int>(tag) == CONSTANT_InterfaceMethodref)
    cout<<setw(20)<<"InterfaceMethodRe";
  else
    cout<<setw(20)<<"UnknownRef";
    
  cout<<setw(15)<<"#"+to_string(classIndex)+".#"+to_string(nameAndTypeIndex);
}

unique_ptr<string>
ConstantRefInfo::getValue(vector<ConstantInfo*>  const& constantPool)
{
  unique_ptr<string> s(new string);
  unique_ptr<string> sNameAndType = constantPool[nameAndTypeIndex]->getValue(constantPool);
  unique_ptr<string> sClass = constantPool[classIndex]->getValue(constantPool);
  *s = *sClass + "." + *sNameAndType;
  return s;
}

void
ConstantStringInfo::load(ifstream& inf)
{
  read_u2(stringIndex, inf);
}

void
ConstantStringInfo::dump()
{
  cout<<setw(20)<<"String"
      <<setw(15)<<"#"+to_string(stringIndex);
}

unique_ptr<string>
ConstantStringInfo::getValue(vector<ConstantInfo*>  const& constantPool)
{
  return constantPool[stringIndex]->getValue(constantPool);
}

void
ConstantUtf8Info::load(ifstream& inf)
{
  read_u2(length, inf);
  bytes.reserve(length+1);
  inf.read(reinterpret_cast<char*>(&bytes[0]), length); 
  bytes[length] = '\0';
}

void
ConstantUtf8Info::dump()
{
  cout<<setw(20)<<"Utf8";
}

unique_ptr<string>
ConstantUtf8Info::getValue(vector<ConstantInfo*>  const& constantPool)
{
  unique_ptr<string> s(new string(bytes.data()));
  return s;
}

void
ConstantIntegerInfo::load(ifstream& inf)
{
  read_u4(bytes, inf);
}

void
ConstantIntegerInfo::dump()
{
  cout<<setw(20)<<"Integer"
      <<setw(15)<<"#"<<bytes;
}

unique_ptr<string>
ConstantIntegerInfo::getValue(vector<ConstantInfo*>  const& constantPool)
{
  unique_ptr<string> s(new string(to_string(bytes)));
  return s;
}

void
ConstantNameAndTypeInfo::load(ifstream& inf)
{
  read_u2(nameIndex, inf);
  read_u2(descriptorIndex, inf);
}

void
ConstantNameAndTypeInfo::dump()
{
  cout<<setw(20)<<"Name And Type"
      <<setw(15)<<"#"+to_string(nameIndex)+".#"+to_string(descriptorIndex);
}

unique_ptr<string>
ConstantNameAndTypeInfo::getValue(std::vector<ConstantInfo*> const& constantPool)
{
  unique_ptr<string> s(new string);
  unique_ptr<string> name = constantPool[nameIndex]->getValue(constantPool);
  unique_ptr<string> descriptor = constantPool[descriptorIndex]->getValue(constantPool);
  *s = *name + ":" + *descriptor;
  return s;
}
