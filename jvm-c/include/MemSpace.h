#ifndef MEM_SPACE_H
#define MEM_SPACE_H

#include <set>
#include <cstddef> //size_t

#include "ObjectRef.h"

class MemSpace
{
  private:
    size_t size_; //this memory space size
    set<ObjectRef*> objects_;
    
  public:
    MemSpace ();
    ~MemSpace ();
    
    void add(ObjectRef* obj);
    void dump ();
};




#endif