/* Copyright 2016 @AR
 *
 * Heap Space : may be EdenSpace, SurvivorSpace, TenuredSpace
 *
 */
#include <unordered_map>
#include <utility> // std::pair
#include <cstddef> //size_t
#include <iostream>
#include <iomanip> //setw
using namespace std;

#include "ObjectRef.h"
#include "ConstantInfo.h"

ObjectRef::ObjectRef (u2 nameIndex, std::string className) 
{ 
  this->nameIndex = nameIndex; 
  this->className = className;
}

ObjectRef::~ObjectRef () 
{
  this->refs = 1;
}
    
void 
ObjectRef::putField (FieldInfo* fieldInfo, j_int_t value)
{
  fields[fieldInfo] = value;
}

void
ObjectRef::initFields ()
{
  for (FieldInfo* fieldInfo : this->clazz->fields)
    this->putField (fieldInfo, 0);
}




