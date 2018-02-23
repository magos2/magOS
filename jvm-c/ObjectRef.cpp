/* Copyright 2016 @AR
 *
 * 
 *
 */
#include <unordered_map>
#include <utility> // std::pair
#include <cstddef> //size_t
#include <iostream>
#include <iomanip> //setw
using namespace std;

#include "ObjectRef.h"


ObjectRef::ObjectRef (u2 nameIndex, char* className) 
{ 
  this->nameIndex = nameIndex; 
  this->className = className;
}

ObjectRef::~ObjectRef () 
{
  this->refs = 1;
}
    
void 
ObjectRef::putField (field_info* fieldInfo, j_int_t value)
{
  fields[fieldInfo] = value;
}

void
ObjectRef::initFields()
{
  int i;
  for (i=0; i < clazz->fields_count; i++)
    this->putField(clazz->fields[i], 0);
}




