
#include <vector>
#include <stack>
#include <string>
#include <cstdlib>
#include <iomanip> //setw
#include <iostream>
using namespace std;

#include "Frame.h"
#include "Types.h"

void
Frame::dump (int depth)
{
  unsigned int i; 
  cout<<hex<<showbase;
  
  cout<<fill_space2(depth)<<setw(3)<<"|"<<"Operand Stack:"<<endl;
  for (i=0; i<operandStack.size(); i++) 
    cout<<fill_space2(depth)<<setw(6)<<"|"<<operandStack[i]<<endl;
  
  cout<<fill_space2(depth)<<setw(3)<<"|"<<"Local vars:"<<endl;
  for (i=0; i<locals.size(); i++)
    cout<<fill_space2(depth)<<setw(6)<<"|"<<locals[i]<<endl;
}