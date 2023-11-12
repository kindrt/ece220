#include <iostream>
#include <string>

using namespace std;

// function template
template <class T>
T sum(T a, T b)
{
    T result;
    result = a + b;
    return result;
}

// class template
template <class T>
class mypair
{
    T values[2];
   public:
    mypair(T a, T b) { values[0] = a; values[1] = b; }
};


int main()
{
    int i=2, j = 3, k;
    double a=2.0, b=0.5, c;

    k = sum(i, j);  // same as sum<int>(i,j)
    c = sum(a, b);  // same as sum<double>(a,b)
    cout << k << endl;
    cout << c << endl;

    cout << sum<string>("Text1 ", "Text 2") << endl;
}

