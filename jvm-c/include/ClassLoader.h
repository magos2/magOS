/* Copyright 2016 @AR
 *
 * BootstrapClassLoader is top classloaders. is usually implemented as native. The bootstrap classloader is responsible 
 * for loading the basic Java APIs(rt.jar). 
 */
#ifndef CLASS_LOADER_H
#define CLASS_LOADER_H

#include <string>
#include <unordered_set>

#include "JavaClass.h"

class ClassLoader {
  public:
    std::unordered_set<JavaClass*> classes; // The classloader contains a reference to all classes that it has loaded.
                                            // All classes that are loaded contain a reference to the classloader that loaded them. 
    
    ClassLoader();
    ~ClassLoader();
    
    JavaClass* load(const std::string classFile);
};

#endif