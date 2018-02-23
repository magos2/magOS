/* Copyright 2016 @AR
 *
 * Mehod Area
 *
 */
#include <set>
#include <cstddef> //size_t
#include <iostream>
#include <iomanip> //setw
using namespace std;

#include "MethodArea.h"

MethodArea::MethodArea ()
{
  size_ = 0;
}

MethodArea::~MethodArea () {}

void 
MethodArea::add (JavaClass* clazz)
{
  classes_.insert (clazz);
  size_ += clazz->size ();
}

void
MethodArea::dump ()
{
  cout<<setw(2)<<""<<"Size : "<<dec<<size_<<" B"<<endl;
  cout<<setw(2)<<""<<"Class list:"<<endl;
  for (JavaClass* clazz : classes_)
    cout<<setw(4)<<""
        <<clazz
        <<" : size="<<clazz->size()<<" B, "<<*clazz->getName()<<endl;
}

