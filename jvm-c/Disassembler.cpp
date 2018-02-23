/* Copyright 2017 @AR
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
#include <unordered_set>
using namespace std;

#include "Disassembler.h"
#include "ClassLoader.h"
#include "JavaClass.h"
#include "JvmEndian.h"
#include "InstructionSet.h"

#define DUMP(member,format)       cout<<setw(25)<<#member ": "<<showbase<<format<<member<<endl        
#define DUMP_HEX(member)          DUMP(member,hex) 
#define DUMP_DEC(member)          DUMP(member,dec) 
#define CP_DUMP1(classe,member)          cout<<setw(30)<<#classe ": "<<#member "="<<dec<<member<<endl
#define CP_DUMP2(classe,member1,member2) cout<<setw(30)<<#classe ": "<<#member1 "="<<dec<<member1<<", " #member2 "="<<member2<<endl

#define HR() cout<<"------------------------"<<endl
#define TAB  cout<<"  "

Disassembler* Disassembler::instance_ = nullptr;

Disassembler*
Disassembler::instance()
{
 if (!instance_)
   instance_ = new Disassembler();
 return instance_;
}

void 
Disassembler::disassemble (JavaClass* clazz)
{
  clazz->disassemble();
}

void 
JavaClass::disassemble ()
{
  int i;
  
  char *class_name = get_class_name(this_class);
  cout<<flags2str(access_flags) <<"class "<< class_name << " {" << endl;
  //fields
  for (i=0; i < fields_count; i++) {
    field_info *field = fields[i];
    TAB;
    cout<<flags2str(field->access_flags)<<get_cp_utf8(field->descriptor_index)<<" "<<get_cp_utf8(field->name_index)<<";"<<endl;
  }
  //methods
  for (i=0; i < methods_count; i++) {
    method_info *method = methods[i];
    Code_attribute* code_attribute = method->code_attribute;
    TAB;
    cout<<flags2str(method->access_flags)<<get_cp_utf8(method->descriptor_index)<<" "<<get_cp_utf8(method->name_index)<<" {"<<endl;
    TAB;TAB;cout<<"max stack: "<<code_attribute->max_stack<<endl;
    TAB;TAB;cout<<"max locals: "<<code_attribute->max_locals<<endl;
    u1 *code = code_attribute->code;
    int n = 0;
    //disassembling method code
    while (n < code_attribute->code_length) {
      int op_code = (int)code[n];
      string mnemonic = byte_code_table[op_code].mnemonic;
      int operand_size = byte_code_table[op_code].operand_size;
      TAB;TAB;cout<<setw(2)<<n<<": "<<mnemonic;
      if (operand_size == 1) {
        int index = (int)code[n+1];
        cout<<" #"<<index;
      }
      else if (operand_size == 2) {
        int indexByte1 = (int)code[n+1];
        int indexByte2 = (int)code[n+2];
        int index = (indexByte1 << 8) | indexByte2;
        cout<<" #"<<index;
        if (op_code == ANEWARRAY || op_code == NEW) 
          cout<<" //"<<get_class_name(index);
        else if (op_code == INVOKESPECIAL || op_code == INVOKESTATIC || op_code == INVOKEVIRTUAL) {
          CONSTANT_Methodref_info *methodref = (CONSTANT_Methodref_info *)get_cp_info(index);
          CONSTANT_NameAndType_info *nameAndType = (CONSTANT_NameAndType_info *)get_cp_info(methodref->name_and_type_index);
          cout<<" //"<<get_class_name(methodref->class_index)<<" "
                     <<get_cp_utf8(nameAndType->name_index)
                     <<get_cp_utf8(nameAndType->descriptor_index);
        }
      }
      else if (operand_size == 4)
        cout<<" #"<<"TODO_";
      cout<<endl;
      n += 1 + operand_size; /*next inatruction*/
    }
    TAB;cout<<"}"<<endl;
  }
}  
  
string flags2str (u2 flags) 
{
  string s = "";
  if (flags & ACC_PUBLIC)
    s += "Public ";
  if (flags & ACC_PRIVATE)
    s += "Private ";
  if (flags & ACC_PROTECTED)
    s += "Protected ";
  if (flags & ACC_STATIC)
    s += "Static ";
  if (flags & ACC_FINAL)
    s += "Final ";
  if (flags & ACC_SYNCHRONIZED)
    s += "Synchronized ";
  if (flags & ACC_BRIDGE)
    s += "Bridge ";
  if (flags & ACC_VARARGS)
    s += "Varags ";
  if (flags & ACC_NATIVE)
    s += "Native ";
  if (flags & ACC_ABSTRACT)
    s += "Abstract ";
  if (flags & ACC_STRICT)
    s += "Strict ";
  if (flags & ACC_SYNTHETIC)
    s += "Synthetic ";
  return s;
}

  
  
  
  






































































