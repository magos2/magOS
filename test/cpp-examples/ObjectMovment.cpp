
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class Pyramid 
{
public:
  int left, right, width;
  Pyramid (int w) { left = right = width = w; }
  
  void draw () 
  {
    int i;
    while (width-- > 0) {
      cout<<setw(left)<< " ";
      for (i = left; i <= right; i++) {
        cout<<".";
        this_thread::sleep_for (chrono::milliseconds(100));
        cout.flush();
      }
      cout<<setw(left)<< " ";
      for (i = left; i <= right; i++) {
        cout<<".";
        this_thread::sleep_for (chrono::milliseconds(100));
        cout.flush();
      }
      cout<<endl;
      left--;
      right++;
    }
  }
};

class Object 
{
  public:
    string s;
    long x, y, pos;
    Object (string s) { this->s = s; x = 0; y = 0; pos = 0;}
    
    void print () {
      cout << s;
      cout.flush ();
      pos += s.size();
    }
    
    void clear  () {
      pos = (long)cout.tellp() - s.size();
      cout.seekp (pos);
      cout<<"  ";
      cout.flush();
      pos += s.size();
      cout.seekp (pos);
    }  
    
    void animate (){
      while (1) {
        print ();
        this_thread::sleep_for (chrono::milliseconds(100));
        clear ();
      }
    }
};

int main (void)
{
  Object  *object;
  Pyramid *pyramid;
  
  object = new Object ("--->");
  //object->animate();
  pyramid = new Pyramid (20);
  pyramid->draw();
  
  return 0;
};

