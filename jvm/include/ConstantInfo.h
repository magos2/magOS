#ifndef CONSTANT_INFO_H
#define CONSTANT_INFO_H
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

class ConstantInfo : public Serializable
{
  public:
    u1 tag;
    
    virtual void dump();
    virtual void load(std::ifstream&);
    
    virtual std::unique_ptr<std::string> getValue (std::vector<ConstantInfo*>  const& constantPool);
};

class ConstantClassInfo : public ConstantInfo 
{
  public:
    u2 nameIndex;
    
    void dump();
    void load(std::ifstream&);
    std::unique_ptr<std::string> getValue (std::vector<ConstantInfo*>  const& constantPool); 
};

/* fieldref-info, methodref-info, interfaceref-info*/
class ConstantRefInfo : public ConstantInfo 
{
  public:
    u2 classIndex;
    u2 nameAndTypeIndex;
  
    void dump();
    void load(std::ifstream&);
    std::unique_ptr<std::string> getValue (std::vector<ConstantInfo*>  const& constantPool);
};

class FieldRefInfo : public ConstantRefInfo {};

class MethodRefInfo : public ConstantRefInfo {};

class InterfaceMethodRefInfo : public ConstantRefInfo {};

class ConstantStringInfo : public ConstantInfo 
{
  public :
    u2 stringIndex;
    
    void dump();
    void load(std::ifstream&);
    std::unique_ptr<std::string> getValue (std::vector<ConstantInfo*>  const& constantPool);
};

class ConstantUtf8Info : public ConstantInfo 
{
  public:
    u2 length;
    std::vector<u1> bytes;
    
    void dump();
    void load(std::ifstream&);
    std::unique_ptr<std::string> getValue (std::vector<ConstantInfo*>  const& constantPool);
};

class ConstantIntegerInfo : public ConstantInfo 
{
  public:
    u4 bytes;
    
    void dump();
    void load(std::ifstream&);
    std::unique_ptr<std::string> getValue (std::vector<ConstantInfo*>  const& constantPool);
};

class ConstantFloatInfo : public ConstantInfo 
{
   u4 bytes;
};

class ConstantLongInfo : public ConstantInfo 
{
   u4 highBytes;
   u4 lowBytes;
};

class ConstantDoubleInfo : public ConstantInfo 
{
   u4 highBytes;
   u4 lowBytes;
};

class ConstantNameAndTypeInfo: public ConstantInfo 
{
  public:
    u2 nameIndex;
    u2 descriptorIndex;
       
    void dump();
    void load(std::ifstream&);
    std::unique_ptr<std::string> getValue (std::vector<ConstantInfo*>  const& constantPool);
};

class ConstantMethodHandleInfo : public ConstantInfo 
{
  public:
    u1 referenceKind;
    u2 referenceIndex;
   
    void dump();
    void load(std::ifstream&);
};

class ConstantMethodTypeInfo : public ConstantInfo 
{
  public:
    u2 descriptorIndex;
    
    void dump();
    void load(std::ifstream&);
};

class ConstantInvokeDynamicInfo : public ConstantInfo
{
 public:
   u2 bootstrapMethodAttrIndex;
   u2 nameAndTypeIndex;
};




#endif
