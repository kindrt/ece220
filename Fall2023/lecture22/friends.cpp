#include <iostream>

using namespace std;

class Square;

class Rectangle
{
    int width, height;

  public:
    Rectangle() {}
    Rectangle(int x, int y) : width(x), height(y) {}
    int area() { return width * height; }

    // friend function
    friend Rectangle duplicate(const Rectangle& param);

    void convert(Square a);
};

class Square
{
   // Rectangle is our friend, its methods can have access to 'side'
   friend class Rectangle;
   private:
      int side;
   public:
      Square(int s) : side(s) {}
};

// friend class
void Rectangle::convert(Square a) 
{ 
    width = height = a.side; 
}

// friend function
Rectangle duplicate(const Rectangle& param)
{
    Rectangle res;
    res.height = param.height;
    res.width = param.width;

    return res;
}


int main()
{
   Rectangle foo;
   Rectangle bar(2, 3);
   foo = duplicate(bar);

   cout << bar.area() << endl;

   Square sqr(4);
   foo.convert(sqr);

   cout << foo.area() << endl;
}

