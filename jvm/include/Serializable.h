#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <fstream>

class Serializable 
{
  public:
    virtual ~Serializable() {};
    
    virtual void dump() = 0;
    virtual void load(std::ifstream&) = 0;
};






#endif