#ifndef FIELD_INFO_H
#define FIELD_INFO_H
/* Copyright 2016 @AR
 * Description of .class jse6
 * https://docs.oracle.com/javase/specs/index.html
 */
#include <vector>
#include <fstream>
#include <string>
#include <memory> //unique_ptr

#include "Types.h"
#include "Serializable.h"
#include "AttributeInfo.h"

class JavaClass;

class FieldInfo : public Serializable
{
  public:
    u2 accessFlags;
    u2 nameIndex;
    u2 descriptorIndex;
    u2 attributesCount;
    std::vector<AttributeInfo*> attributes;
    
    JavaClass* clazz; // class to wich this field belong 
    
    FieldInfo (JavaClass* clazz) { this->clazz = clazz; }
    ~FieldInfo () {}
    void dump();
    void load(std::ifstream&);
    std::string getDescription();
};

#endif
