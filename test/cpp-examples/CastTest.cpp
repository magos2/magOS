#include <iostream>
using namespace std ;

class Point
{
 public : 
   int x, y ;

   Point (int abs=0, int ord=0) // constructeur 0, 1 ou 2 arguments
   { 
     x = abs ; y = ord ;
     cout << "++ construction point : " << x << " " << y << endl ;
   }
   
   Point (Point const& p) 
   { 
     cout << "== Appel de constructeur de copie"<<endl;
     x = p.x; y = p.y; 
   }
   
   operator int() // "cast" point --> int
   { 
     cout << "== appel int() pour le point " << x << " " << y << endl ;
     return x ;
   }
};

int main()
{ 
 Point a(3,4), b(5,7), c;
 
 Point* p1 = new Point(a); // appel constructeur de copie
 Point* p2 = new Point(6,8);
 
 cout <<"&a="<<&a<<endl;
 cout <<"p1="<<p1<<endl;
 cout <<"p2="<<p2<<endl;
 
 int n1, n2 ;
 n1 = int(a) ; // appel explicite de int ()
               // on peut aussi écrire : n1 = (int) a ou n1 = static_cast<int> (a)
 cout << "n1 = " << n1 << endl ; 
 
 n2 = b ; // appel implicite de int()
 cout << "n2 = " << n2 << endl ;
 
 
 c = a;
 cout << "&c="<<&c
      << ", c.x="<<c.x<<" ,c.y="<<c.y<<endl;
 
 cout <<"p1="<<p1
      << ", p1->x="<<p1->x<<" ,p1->y="<<p1->y<<endl;
 return 0;
} 
