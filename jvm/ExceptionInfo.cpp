/* Copyright 2016 @AR
 *
 * Description of .class jse6
 * https://docs.oracle.com/javase/specs/index.html
 */
#include <iostream> //cout, hex, dec
#include <fstream>
#include <cstdlib>
#include <iomanip> //setw
#include <typeinfo> //typeid get classname
#include <memory> //unique_ptr
using namespace std;

#include "ExceptionInfo.h"
#include "JavaClass.h"
#include "JvmEndian.h"
#include "ConstantTag.h"
#include "FStreamUtils.h"
#include "Disassembler.h"
#include "AccessFlags.h"


void
ExceptionInfo::load(ifstream& inf)
{
  read_u2(startPc, inf);
  read_u2(endPc, inf);
  read_u2(handlerPc, inf);
  read_u2(catchType, inf);
}

void
ExceptionInfo::dump()
{
  cout<<"\t"<<"ExceptionInfo:"<<endl;
  cout<<hex<<showbase;
  cout<<"\t\t"<<"startPc: "<<dec<<startPc<<endl;
  cout<<"\t\t"<<"endPc: "<<dec<<endPc<<endl;
  cout<<"\t\t"<<"handlerPc: "<<dec<<handlerPc<<endl;
  cout<<"\t\t"<<"catchType: "<<dec<<catchType<<endl;
}
