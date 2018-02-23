#ifndef METHOD_AREA_H
#define METHOD_AREA_H

#include <set>
#include <cstddef>

#include "JavaClass.h"

class MethodArea
{
  private:
    size_t size_;
    std::set<JavaClass*> classes_;
  public:
    MethodArea ();
    ~MethodArea ();
    
    void add (JavaClass*);
    void dump ();
};




#endif
