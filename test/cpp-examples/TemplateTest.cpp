#include <iostream>
#include <vector>
#include <string>
using namespace std;

/////////////////////////
// class template
//
/////////////////////////
template <class T> class Pile {
  private:
    vector<T> elems;
  
  public:
    void push (T const&);
    T pop ();
};

template <class T>
void Pile<T>::push (T const& v) {
      elems.push_back(v);
  }

template <class T>
T Pile<T>::pop ()
{ 
  T v = elems.back();
  elems.pop_back(); //delete last elem
  return v; 
} 

///////////////////////
//Function template
//
///////////////////////
template <typename T> 
T const&	  max2(T const& a, T const& b)
{
  return (a>b)?a:b;
};

///////////////////////
int main() {
///////////////////////
  // testing class template
  Pile<string> pile;
  pile.push("Anass");
  cout<<"Stack top: ";
  cout<<pile.pop()<<endl;
  
  // testing function template
  cout<<"max int 30 , 50 : "
      <<max2(30,50)<<endl;
  cout<<"max string aaa fff :"
      <<max2("aaa", "fff")<<endl;
  return 0;
}