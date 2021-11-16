
#include <iostream>
#include <string>

using namespace std;

class Example
{
    string *ptr;

  public:
    // default constructor
    Example() : ptr(new string) { }

    Example(const string& str) : ptr(new string(str)) { }

    // default destructor    
    ~Example() { delete ptr; }

    // copy constructor
    Example(const Example& x) : ptr(new string(x.content())) { }

    // copy assignment
    Example& operator= (const Example& x)
    {
        delete ptr;  // make sure no mem is lost
        ptr = new string(x.content());
        return *this;
    }

    const string& content() const { return *ptr; }
    
};

int main()
{
    Example bar("Example");
    cout << bar.content() << endl;

    Example tor(bar);  // uses copy constructor
    cout << tor.content() << endl;

    Example foo;  // uses default constructor
    Example baz = foo;   // Example baz(foo);  <- uses copy constructor

    foo = tor;  // copy assignment operator is called here
    cout << foo.content() << endl;
}


