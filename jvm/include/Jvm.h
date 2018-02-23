#ifndef JVM_H
#define JVM_H

#include "MemSpace.h"
#include "MethodArea.h"
#include "ClassLoader.h"
#include "JavaClass.h"
#include "Interpreter.h"
#include "Disassembler.h"

class Jvm
{
  private:
    static Jvm* instance_;
    Jvm ();
    ~Jvm ();
    
  public:
    //Heap memory
    MemSpace* edenSpace;
    MemSpace* survivorSpace;
    MemSpace* tenuredSpace;
    
    //No-Heap Memory
    MethodArea* methodArea;
    MemSpace* permanentGen; // permanent generation
    MemSpace* cache;
    
    static Jvm* Runtime();
    ClassLoader* classLoader;
    Interpreter* interpreter;
    //GarbageCollector* garbageCollector;
    
    void startup();
    void shutdown();
};




#endif