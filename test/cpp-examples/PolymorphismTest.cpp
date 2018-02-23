
class Shape 
{
  public:
    virtual int surface() = 0;
};

class Rectangle : public Shape
{
  public:
    int a, b;
   
    Rectangle(int a, int b) {this->a=a;this->b=b; };
    int surface();
};

class Circle : public Shape
{
  public:
    int r;
    
    Circle(int r) {this->r=r; };
    int surface();
};

int
Rectangle::surface()
{
  return a*b;
}

int
Circle::surface()
{
  return r*r/2; //je sais plus
}

int main()
{
  Shape* s;
  
  s = new Rectangle(2,3);
  s->surface();
  s = new Circle(10);
}






