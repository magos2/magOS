/* Copyright 2016 @AR
 *
 * JVM core : i'am developping this jvm to deeply understand java
 *
 */
#include <string>
#include <iostream>
using namespace std;

#include "Jvm.h"
#include "JavaClass.h"
#include "ClassLoader.h"
#include "Disassembler.h"

Jvm* Jvm::instance_ = nullptr;

Jvm*
Jvm:: Runtime ()
{
 if (!instance_)
   instance_ = new Jvm();
 return instance_;
}

Jvm::Jvm ()
{
  this->classLoader = new ClassLoader();
}

Jvm::~Jvm ()
{
  delete this->classLoader;
}

void
Jvm::shutdown ()
{
  delete instance_;
  exit(EXIT_SUCCESS);
}

int main(int nargs, char** argv)
{
  int i;
  JavaClass* clazz;
  string class_path = "/usr/local/test/Hello.class";
  int opt_p = 0;
  //parsing options
  for (i=1; i<nargs; i++) {
     if (string(argv[i]) == "-p")
       opt_p = 1;
     else
       class_path = string(argv[i]);
  }
  clazz = Jvm::Runtime()->classLoader->load (class_path);
  if (!clazz)
    goto end;
  if (opt_p)
    Disassembler::instance()->disassemble(clazz);
      
  cout<<"Interpreting the Class"<<endl;

end:
  Jvm::Runtime()->shutdown ();
  //delete clazz;
  return 0;
}

















