// to compile: g++ vector.cpp

#include <iostream>
#include <math.h>

using namespace std;

class vector
{
     protected:
        double lenght, angle;

     public:
        vector() { lenght = angle = 0.0; }
        vector(double l, double a) { lenght = l; angle = a; }

        double getAngle() { return angle; }
        double getLenght() { return lenght; }
        
        void setAngle(double a) { angle = a; }
        void setLenght(double l) { if (l >=0 ) lenght = l; }
        
        void scale(double alpha) { lenght *= alpha; }
        vector add(vector b);
        
};

vector vector::add(vector b)
{
     vector c;
     
     double ax = lenght * cos(angle);
     double ay = lenght * sin(angle);

     double bx = b.lenght * cos(b.angle);
     double by = b.lenght * sin(b.angle);
     
     double cx = ax + bx;
     double cy = ay + by;

     c.lenght = sqrt(cx*cx+cy*cy); 
     c.angle = acos(cx/c.lenght);
     
     return c;
}


int main()
{
      vector a;
      vector b(2, 1.5);
      vector c;
      double an, le;
      string s = "C++: ";

      //scanf("%lf %lf", &an, &le);
      cin >> an >> le;
      
      a.setAngle(an);
      a.setLenght(le);
      
      c = a.add(b);
      
      //printf("C: %f, %f\n", c.getLenght(), c.getAngle());
      cout << s << c.getLenght() << ", " << c.getAngle() << endl;

      return 0;
}

