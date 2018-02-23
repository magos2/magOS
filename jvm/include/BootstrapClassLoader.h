/* Copyright 2016 @AR
 *
 * BootstrapClassLoader is top classloaders. is usually implemented as native. The bootstrap classloader is responsible 
 * for loading the basic Java APIs(rt.jar). 
 */
#ifndef BOOTSTRAP_CLASS_LOADER_H
#define BOOTSTRAP_CLASS_LOADER_H

#include <string>
#include <unordered_set>

#include "JavaClass.h"

class BootstrapClassLoader : public ClassLoader {
  
};

#endif