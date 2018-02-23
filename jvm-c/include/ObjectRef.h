#ifndef OBJECT_REF_H
#define OBJECT_REF_H

#include <string>
#include <unordered_map>

#include "Types.h"
#include "JavaClass.h"

class ObjectRef 
{
  public:
    u2 nameIndex;
    char* className; // java name of this object
    unordered_map<field_info*,j_int_t> fields; //map <field_info*,value> 
    JavaClass* clazz;
    int refs; // how many times this object is referenced.
              // it may be garbage collected if refs=0
              // instructions that increment refs : new
              // instructions that decrement refs : 
 public:
    ObjectRef (u2 nameIndex, char* className);
    ~ObjectRef ();
    void initFields();
    void putField (field_info*, j_int_t value);
};




#endif