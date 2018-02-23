#ifndef _JVM_CLASS_H
#define _JVM_CLASS_H
/* C@ AR 2017
 * Description of Class File format. JVM 8
 *
 * see https://docs.oracle.com/javase/specs/
 */

#include "Types.h"
#define __packed__ __attribute((packed))

class JavaClass;

class Serializable {
  public:
    virtual int load (char *& buf) = 0;
};

/*Constant Pool tags*/
#define CONSTANT_Class                  7
#define CONSTANT_Fieldref               9
#define CONSTANT_Methodref             10
#define CONSTANT_InterfaceMethodref    11
#define CONSTANT_String                 8
#define CONSTANT_Integer                3
#define CONSTANT_Float                  4
#define CONSTANT_Long                   5
#define CONSTANT_Double                 6 
#define CONSTANT_NameAndType           12
#define CONSTANT_Utf8                   1
#define CONSTANT_MethodHandle          15
#define CONSTANT_MethodType            16
#define CONSTANT_InvokeDynamic         18

/*Constant Pool Info*/
class cp_info : public Serializable {
  public:
    u1 tag;
    
};

class CONSTANT_Class_info : public cp_info {
  public:
    u2 name_index;
    virtual int load (char *& buf);
};

class CONSTANT_Ref_info : public cp_info {
  public:
    u2 class_index;
    u2 name_and_type_index;
    virtual int load (char *& buf);
};

class CONSTANT_Fieldref_info : public CONSTANT_Ref_info {};

class CONSTANT_Methodref_info : public CONSTANT_Ref_info {};

class CONSTANT_InterfaceMethodref_info : public CONSTANT_Ref_info {};

class CONSTANT_String_info : public cp_info {
  public:
    u2 string_index;  
    virtual int load (char *& buf);
    
};

class CONSTANT_Integer_info : public cp_info {
  public:
    u4 bytes;
    virtual int load (char *& buf);
};

class CONSTANT_Float_info : public cp_info {
  public:
    u4 bytes;
    virtual int load (char *& buf);
};

class CONSTANT_Long_info : public cp_info {
  public:
    u4 high_bytes;
    u4 low_bytes;
    virtual int load (char *& buf);
};

class CONSTANT_Double_info : public cp_info {
  public:
    u4 high_bytes;
    u4 low_bytes;
    virtual int load (char *& buf);
};

class CONSTANT_NameAndType_info : public cp_info {
  public:
    u2 name_index;
    u2 descriptor_index;
    virtual int load (char *& buf);
};

class CONSTANT_Utf8_info : public cp_info {
  public:
    u2 length;
    u1 *bytes; //u1 bytes[length];
    virtual int load (char *& buf);
};

class CONSTANT_MethodHandle_info : public cp_info {
  public:
    u1 reference_kind;
    u2 reference_index;
    virtual int load (char *& buf);
};

class CONSTANT_MethodType_info : public cp_info {
  public:
    u2 descriptor_index;
    virtual int load (char *& buf);
};

class CONSTANT_InvokeDynamic_info : public cp_info {
  public:
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
    virtual int load (char *& buf);
};

class attribute_info {
  public:
    u2 attribute_name_index;
    u4 attribute_length;
    virtual int load (char *& buf, JavaClass *clazz);
};

class ConstantValue_attribute : public attribute_info {
  public:
    u2 constantvalue_index;
    virtual int load (char *& buf, JavaClass *clazz);
};

class exception_info {   
  public:
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
    int load (char *& buf);
    void dump();
};
    
class Code_attribute : public attribute_info {
  public:
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code; //code[code_length]
    u2 exception_table_length;
    exception_info *exception_table; //exception_table[exception_table_length];
    u2 attributes_count;
    attribute_info **attributes; //attributes[attributes_count];
    virtual int load (char *& buf, JavaClass *clazz);
};

class SourceFile_attribute : public attribute_info {
  public:
    u2 sourcefile_index;
    virtual int load (char *& buf, JavaClass *clazz);
};

class line_number_info { 
  public:
    u2 start_pc;
    u2 line_number;	
}; 
    
class LineNumberTable_attribute : public attribute_info {
  public:
    u2 line_number_table_length;
    line_number_info *line_number_table;//line_number_table[line_number_table_length];
    virtual int load (char *& buf, JavaClass *clazz);
};


/*Fiels*/
class field_info {
  public:
    u2             access_flags;
    u2             name_index;
    u2             descriptor_index;
    u2             attributes_count;
    attribute_info **attributes; //attributes[attributes_count];
    int load (char *& buf, JavaClass *clazz);
};

class method_info {
  public:
    u2             access_flags;
    u2             name_index;
    u2             descriptor_index;
    u2             attributes_count;
    attribute_info **attributes; //attributes[attributes_count];
    Code_attribute *code_attribute;
    int load (char *& buf, JavaClass *clazz);
};

/*Java Class File Format*/ 
class JavaClass {
  public:
    u4             magic;
    u2             minor_version;
    u2             major_version;
    u2             constant_pool_count;
    cp_info      **constant_pool; //constant_pool[constant_pool_count-1];
    u2             access_flags;
    u2             this_class;
    u2             super_class;
    u2             interfaces_count;
    u2            *interfaces;//interfaces[interfaces_count];
    u2             fields_count;
    field_info   **fields;  //fields[fields_count];
    u2             methods_count;
    method_info  **methods; //methods[methods_count];
    u2             attributes_count;
    attribute_info **attributes; //attributes[attributes_count];    
    method_info *main; /*the main*/

    int load (char *& buf); /*ClassLoader.cpp*/
    void disassemble ();    /*Disassembler.cpp*/
    cp_info* get_cp_info(u2 index);
    char* get_cp_string(u2 index, char *buf);
    char * get_class_name(u2 class_index);
    char * get_method_name(method_info *method);  
    char* get_cp_utf8(u2 index); /*index must point to CONSTANT_Utf8*/
    
};

#define EBADFORMAT 1

/*field and method flags*/
#define ACC_PUBLIC        0x0001	//Declared public; may be accessed from outside its package.
#define ACC_PRIVATE       0x0002	//Declared private; accessible only within the defining class.
#define ACC_PROTECTED     0x0004	//Declared protected; may be accessed within subclasses.
#define ACC_STATIC        0x0008	//Declared static.
#define ACC_FINAL         0x0010	//Declared final; must not be overridden (§5.4.5).
#define ACC_SYNCHRONIZED  0x0020	//Declared synchronized; invocation is wrapped by a monitor use.
#define ACC_BRIDGE        0x0040	//A bridge method, generated by the compiler.
#define ACC_VARARGS       0x0080	//Declared with variable number of arguments.
#define ACC_NATIVE        0x0100	//Declared native; implemented in a language other than Java.
#define ACC_ABSTRACT      0x0400	//Declared abstract; no implementation is provided.
#define ACC_STRICT        0x0800	//Declared strictfp; floating-point mode is FP-strict.
#define ACC_SYNTHETIC     0x1000	//Declared synthetic; not present in the source code.

string flags2str (u2 flags);












#endif
