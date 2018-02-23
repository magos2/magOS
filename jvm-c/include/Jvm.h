#ifndef JVM_H
#define JVM_H

#include "ClassLoader.h"
#include "JavaClass.h"

class Jvm
{
  private:
    static Jvm* instance_;
    Jvm ();
    ~Jvm ();
    
  public:
 
    static Jvm* Runtime();
    ClassLoader* classLoader;
 
    void startup();
    void shutdown();
};




#endif