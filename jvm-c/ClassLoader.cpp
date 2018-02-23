/* Copyright 2016 @AR
 *
 * Class Loader helper
 */
#include <cstdlib> //exit
#include <iostream> //cout, hex, dec
#include <fstream>
#include <cstdlib>
#include <iomanip> //setw
#include <string>
#include <cstring> //strncpy
#include <cstddef> //offsetof
#include <cstdio> //printf
#include <unordered_set>
using namespace std;
 
#include "ClassLoader.h"
#include "JavaClass.h"
#include "JvmEndian.h"


#define DEBUG 0

#define DUMP(member,format)       cout<<setw(25)<< #member ": "<<showbase<<format<<member<<endl        
#define DUMP_HEX(member)          DUMP(member,hex) 
#define DUMP_DEC(member)          DUMP(member,dec) 

#define LOADM(member,type,buf)  (member)=*(type *)buf;  \
                                swap_##type(member);    \
                                buf += sizeof(type); 
#if DEBUG
#define LOAD(member,type,buf)   LOADM(member,type,buf) \
                                DUMP_DEC(member); 
#define debug(...) do {\
                   printf ("debug: ");\
                   printf(__VA_ARGS__);\
                   printf("\n");\
                   }while(0)
                                                  
#else
#define LOAD(member,type,buf)   LOADM(member,type,buf)   
#define debug(...)   
#endif                               

ClassLoader::ClassLoader() {}
ClassLoader::~ClassLoader() {}

JavaClass*
ClassLoader::load(const string classFile) 
{
  int err;
  char *buf;
  JavaClass* clazz;
  ifstream inf;
  
  inf.open(classFile.c_str(), ios::binary | ios::in);
  if (!inf.good()) {
    string msg ("opening file ");
    msg += classFile;
    perror(msg.c_str()) ;
    exit(EXIT_FAILURE);
  }

  //load class
  inf.seekg(0, ios::end);
  int fsize = inf.tellg();
  cout<<"File size: "<<dec<<fsize<<" Bytes"<<endl;
  inf.seekg(0);
  buf = new char[fsize];
  inf.read(buf, fsize);
  clazz = new JavaClass();
  err = clazz->load(buf);
  if (err < 0)
    goto bad_class_format;
  this->classes.insert (clazz);    
  return clazz;
bad_class_format:  
  delete[] clazz->constant_pool;
  delete clazz;
  return NULL;
}

int 
JavaClass::load (char *& buf)
{
  int i;
  cp_info * cpinfo;
  u1 tag;
  
  /*header*/
  LOAD(magic, u4, buf); 
  LOAD(minor_version, u2, buf);
  LOAD(major_version, u2, buf);
  /*reading contant pool*/
  LOAD(constant_pool_count, u2, buf);
  constant_pool = new cp_info*[constant_pool_count-1];
  for (i=0; i < constant_pool_count - 1; i++) {
    tag = *buf;
    switch (tag) {
    case CONSTANT_Class              : cpinfo = new CONSTANT_Class_info;      break;
    case CONSTANT_Fieldref           : cpinfo = new CONSTANT_Fieldref_info;   break;
    case CONSTANT_Methodref          : cpinfo = new CONSTANT_Methodref_info;  break;
    case CONSTANT_InterfaceMethodref : cpinfo = new CONSTANT_InterfaceMethodref_info;  break;
    case CONSTANT_String             : cpinfo = new CONSTANT_String_info;   break;
    case CONSTANT_Integer            : cpinfo = new CONSTANT_Integer_info;  break;
    case CONSTANT_Float              : cpinfo = new CONSTANT_Float_info;    break;
    case CONSTANT_Long               : cpinfo = new CONSTANT_Long_info;     break;
    case CONSTANT_Double             : cpinfo = new CONSTANT_Double_info;   break;
    case CONSTANT_NameAndType        : cpinfo = new CONSTANT_NameAndType_info;    break;
    case CONSTANT_Utf8               : cpinfo = new CONSTANT_Utf8_info;           break;
    case CONSTANT_MethodHandle       : cpinfo = new CONSTANT_MethodHandle_info;   break;
    case CONSTANT_MethodType         : cpinfo = new CONSTANT_MethodType_info;     break;
    case CONSTANT_InvokeDynamic      : cpinfo = new CONSTANT_InvokeDynamic_info;  break;
    default:
      cout <<"Bad class file, unknown constant pool tag: " <<(int)tag <<" at i="<<i<<endl;
      goto bad_file_format;
    }
    cpinfo->load(buf);
    constant_pool[i] = cpinfo;
  } 
  LOAD(access_flags, u2, buf);
  LOAD(this_class, u2, buf);
  LOAD(super_class, u2, buf);
  //interfaces; TODO
  LOAD(interfaces_count, u2, buf);
  interfaces = new u2[interfaces_count];
  for (i=0; i < interfaces_count; i++) {
    u2 tmp;
    LOAD(tmp, u2, buf);
    interfaces[i] = tmp;
  }
  //fields
  LOAD(fields_count, u2, buf);
  fields = new field_info*[fields_count];
  for (i=0; i < fields_count; i++) {
    debug("load field #%d", i);
    fields[i] = new field_info;
    fields[i]->load(buf, this);
  }
  //methods
  LOAD(methods_count, u2, buf);
  methods = new method_info*[methods_count];
  for (i=0; i < methods_count; i++) {
    debug("load method #%d", i);
    methods[i] = new method_info;
    methods[i]->load(buf, this);
    if (strcmp(get_method_name(methods[i]), "main") == 0)
      main = methods[i];
  }
  //attributes 
  LOAD(attributes_count, u2, buf);
  attributes = new attribute_info*[attributes_count];
  for (i=0; i < attributes_count; i++) {
    debug("load class attribute #%d", i);
    u2 attr_name_index =  *(u2 *)buf;
    swap_u2(attr_name_index);
    char* attr_name = get_cp_utf8(attr_name_index);
    if (strcmp(attr_name, "SourceFile") == 0) {
      attributes[i] = new SourceFile_attribute;
      attributes[i]->load(buf, this);
    }
    else {
      cout<<"unknown or not yet implemented attribute "<<attr_name<<endl;
      goto bad_file_format;
    }
  }
  return 0;
bad_file_format:
  return -EBADFORMAT;
}

cp_info* 
JavaClass::get_cp_info(u2 index)
{
  return this->constant_pool[index-1];
}

char* 
JavaClass::get_cp_utf8(u2 index)
{
  return ((CONSTANT_Utf8_info *)get_cp_info(index))->bytes;
}

char* 
JavaClass::get_class_name(u2 class_index)
{
  CONSTANT_Class_info *cpi_class = (CONSTANT_Class_info *)get_cp_info(class_index);
  return get_cp_utf8(cpi_class->name_index);
}

char* 
JavaClass::get_method_name(method_info *method)
{
  return get_cp_utf8(method->name_index);
}


int 
CONSTANT_Class_info::load (char *& buf)
{
  LOAD(tag, u1, buf);
  LOAD(name_index, u2, buf);
  return 0;
}

int 
CONSTANT_Ref_info::load (char *& buf)
{
  LOAD(tag, u1, buf);
  LOAD(class_index, u2, buf);
  LOAD(name_and_type_index, u2, buf);
  return 0;
}

int 
CONSTANT_String_info::load (char *& buf)
{
  LOAD(tag, u1, buf);
  LOAD(string_index, u2, buf);
  return 0;
}

int 
CONSTANT_Integer_info::load (char *& buf)
{
  LOAD(tag, u1, buf);
  LOAD(bytes, u4, buf);
  return 0;
}  

int 
CONSTANT_Float_info::load (char *& buf)
{
  LOAD(tag, u1, buf);
  LOAD(bytes, u4, buf);
  return 0;
}  

int 
CONSTANT_Long_info::load (char *& buf)
{
  LOAD(tag, u1, buf);
  LOAD(high_bytes, u4, buf);
  LOAD(low_bytes, u4, buf);
  return 0;
}  

int 
CONSTANT_Double_info::load (char *& buf)
{
  LOAD(tag, u1, buf);
  LOAD(high_bytes, u4, buf);
  LOAD(low_bytes, u4, buf);
  return 0;
}  

int 
CONSTANT_NameAndType_info::load (char *& buf)
{
  LOAD(tag, u1, buf);
  LOAD(name_index, u2, buf);
  LOAD(descriptor_index, u2, buf);
  return 0;
}

int 
CONSTANT_MethodHandle_info::load (char *& buf)
{
  LOAD(tag, u1, buf);
  LOAD(reference_kind, u1, buf);
  LOAD(reference_index, u2, buf);
  return 0;
}

int 
CONSTANT_MethodType_info::load (char *& buf)
{
  LOAD(tag, u1, buf);
  LOAD(descriptor_index, u2, buf);
  return 0;
}

int 
CONSTANT_InvokeDynamic_info::load (char *& buf)
{
  LOAD(tag, u1, buf);
  LOAD(bootstrap_method_attr_index, u2, buf);
  LOAD(name_and_type_index, u2, buf);
  return 0;
}

int 
CONSTANT_Utf8_info::load (char *& buf)
{
  LOAD(tag, u1, buf);
  LOAD(length, u2, buf);
  bytes = new char[length+1];
  strncpy (bytes, buf, length);
  bytes[length] = '\0';
  buf += length;
  return 0;
}  
  
int 
field_info::load (char *& buf, JavaClass *clazz)
{
  int i;
  LOAD(access_flags, u2, buf);
  LOAD(name_index, u2, buf);
  LOAD(descriptor_index, u2, buf);
  LOAD(attributes_count, u2, buf);
  attributes = new attribute_info*[attributes_count];
  for (i=0; i < attributes_count; i++) {
	u2 attr_name_index =  *(u2 *)buf;
	swap_u2(attr_name_index);
    char* attr_name = (char *)clazz->get_cp_info(attr_name_index);
    if (strcmp(attr_name, "ConstantValue") == 0) {
      attributes[i] = new ConstantValue_attribute;
      attributes[i]->load(buf,clazz);
    }
    else {
      cout<<"unknown or not yet implemented attribute "<<attr_name<<endl;
      return -EBADFORMAT;
    }
  }
  return 0;
}

int 
method_info::load (char *& buf, JavaClass *clazz)
{
  int i;
  
  LOAD(access_flags, u2, buf);
  LOAD(name_index, u2, buf);
  LOAD(descriptor_index, u2, buf);
  LOAD(attributes_count, u2, buf);
  attributes = new attribute_info*[attributes_count];
  for (i=0; i < attributes_count; i++) {
    u2 attr_name_index =  *(u2 *)buf;
    swap_u2(attr_name_index);
    char* attr_name = clazz->get_cp_utf8(attr_name_index);
    if (strcmp(attr_name, "Code") == 0) {
      attributes[i] = code_attribute = new Code_attribute;
      attributes[i]->load(buf, clazz);
    }
    else if (strcmp(attr_name, "LineNumberTable") == 0) {
      attributes[i] = new LineNumberTable_attribute;
      attributes[i]->load(buf, clazz);
    }
    else {
      cout<<"error loading method_info: not yet implemented attribute "<<attr_name<<endl;
      return -EBADFORMAT;
    }
  }
  return 0;
}

int 
attribute_info::load (char *& buf, JavaClass *clazz)
{
  LOAD(attribute_name_index, u2, buf);
  LOAD(attribute_length, u4, buf);
  return 0;
}

int 
ConstantValue_attribute::load (char *& buf, JavaClass *clazz)
{
  attribute_info::load(buf, clazz);
  LOAD(constantvalue_index, u2, buf);
  return 0;
}

int 
Code_attribute::load (char *& buf, JavaClass *clazz)
{
  int i;
  
  attribute_info::load(buf,clazz);
  LOAD(max_stack, u2, buf);
  LOAD(max_locals, u2, buf);
  LOAD(code_length, u4, buf);
  code = new u1[code_length];
  memcpy (code, buf, code_length);
  buf += code_length;
  LOAD(exception_table_length, u2, buf);
  exception_table = new exception_info[exception_table_length];
  for (i=0; i < exception_table_length; i++) {
    exception_table[i].load(buf);
  }
  LOAD(attributes_count, u2, buf);
  attributes = new attribute_info*[attributes_count];
  for (i=0; i < attributes_count; i++) {
    u2 attr_name_index =  *(u2 *)buf;
    swap_u2(attr_name_index);
    char* attr_name = clazz->get_cp_utf8(attr_name_index);
    if (strcmp(attr_name, "LineNumberTable") == 0) {
      attributes[i] = new LineNumberTable_attribute;
      attributes[i]->load(buf, clazz);
    }
    else {
      cout<<"error loading code_attribute: not yet implemented attribute "<<attr_name<<endl;
      return -EBADFORMAT;
    }
    return -1;
  }
  return 0;
}

int 
SourceFile_attribute::load (char *& buf, JavaClass *clazz)
{
  attribute_info::load(buf,clazz);
  LOAD(sourcefile_index, u2, buf);
  return 0;
}

int 
LineNumberTable_attribute::load (char *& buf, JavaClass *clazz)
{
  int i;
  attribute_info::load(buf,clazz);
  LOAD(line_number_table_length, u2, buf);
  line_number_table = new line_number_info[line_number_table_length];
  for (i=0; i < line_number_table_length; i++) {
    LOAD(line_number_table[i].start_pc, u2, buf);
    LOAD(line_number_table[i].line_number, u2, buf);
  }
  return 0;
}

int 
exception_info::load (char *& buf)
{
  LOAD(start_pc, u2, buf);
  LOAD(end_pc, u2, buf);
  LOAD(handler_pc, u2, buf);
  LOAD(catch_type, u2, buf);
  return 0;
}








  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
