
class Hello {
  public:
    int pow2 (int n);
    Hello();
    ~Hello();
};

Hello::Hello () {};
Hello::~Hello () {};

int
Hello::pow2 (int n)
{
  return (1 << n);
}


int main ()
{
  Hello* hello = new Hello();
  hello->pow2(100);
  hello->pow2(5);
  
  return 0;
}