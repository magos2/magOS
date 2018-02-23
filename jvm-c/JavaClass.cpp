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

#if DEBUG
#define debug(...) do {\
                   printf ("debug: ");\
                   printf(__VA_ARGS__);\
                   printf("\n");\
                   }while(0)                                                  
#else
#define debug(...)   
#endif                               

JavaClass::JavaClass() {}
JavaClass::~JavaClass() {}

method_info*
JavaClass::resolve_method(u4 methodref)
{
  int i;
  CONSTANT_Methodref_info* methodref_info = (CONSTANT_Methodref_info *)get_cp_info(methodref);
  if (this->this_class != methodref_info->class_index)
    fatal("we cannot resolve method in other class than current!"); 
  for (i=0; i < methods_count; i++) {
    method_info* method = methods[i];
    if (this->methodref_info->
  }
}






























