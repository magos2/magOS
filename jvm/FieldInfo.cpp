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

#include "FieldInfo.h"
#include "JavaClass.h"
#include "JvmEndian.h"
#include "ConstantTag.h"
#include "FStreamUtils.h"
#include "Disassembler.h"
#include "AccessFlags.h"


void
FieldInfo::load(ifstream& inf)
{
  int i;
  read_u2(accessFlags, inf);
  read_u2(nameIndex, inf);
  read_u2(descriptorIndex, inf);
  read_u2(attributesCount, inf);
  attributes.reserve(attributesCount);
  for (i=0; i<attributesCount; i++) {
    AttributeInfo* attribute = new AttributeInfo();
    attribute->load(inf);
    attributes.push_back (attribute);
  }
}

void
FieldInfo::dump()
{
  cout<<dec<<setw(3)<<""
      <<*clazz->getConstantValue(descriptorIndex)<<" "
      <<*clazz->getConstantValue(nameIndex)<<": "
      "#"<<nameIndex<<".#"<<descriptorIndex<<endl;
  cout<<"\t"<<"access flags: "<<access_flag_lebel(accessFlags)<<endl;
  cout<<"\t"<<"attributesCount: "<<dec<<attributesCount<<endl;

  for (AttributeInfo* attribute : this->attributes)
     attribute->dump();
}



