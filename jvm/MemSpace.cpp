/* Copyright 2016 @AR
 *
 * Heap Space : may be EdenSpace, SurvivorSpace, TenuredSpace
 *
 */
#include <set>
#include <cstddef> //size_t
#include <iostream>
#include <iomanip> //setw
using namespace std;

#include "MemSpace.h"

MemSpace::MemSpace ()
{
  size_ = 0;
}

MemSpace::~MemSpace () {}

void 
MemSpace::add (ObjectRef* obj)
{
  objects_.insert (obj);
  size_ += sizeof (*obj);
}

void
MemSpace::dump ()
{
  cout<<setw(2)<<""<<"Size : "<<dec<<size_<<" B"<<endl;
  cout<<setw(2)<<""<<"Object list:"<<endl;
  for (ObjectRef const* obj : objects_) {
    cout<<setw(4)<<""
        <<obj
        <<" : size="<<sizeof(*obj)<<" B, "<<obj->className;
    cout<<", fields: "; 
    for (auto const& element : obj->fields)
      cout<<element.first<<"="<<element.second<<", ";
    cout<<endl;
  }
}