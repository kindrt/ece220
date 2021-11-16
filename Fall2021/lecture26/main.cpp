
// compile with g++ main.cpp

#include <iostream>
#include "list.h"
#include "stack.h"


using namespace std;
using namespace ece220;

int main() {

    cout << "List of ints" << endl; 

    List<int> li;

    cout << li << endl;

    li.insertFront(1);
    li.insertFront(2);

    cout << li << endl;

    cout << li.size() << endl;

    cout << "Another List of ints" << endl; 
    List<int> li2(li);
    cout << li2 << endl;

    cout << "List of strings" << endl; 

    List<string> ls;

    cout << ls << endl;

    ls.insertFront("one");
    ls.insertFront("two");
    ls.insertFront("three");

    cout << ls << endl;

    cout << ls.size() << endl;


    cout << "Stack of floats" << endl; 

    Stack<double> sf;

    cout << sf << endl;

    sf.push(1.1);
    sf.push(2.2);
    sf.push(3.3);

    cout << sf << endl;

    sf.pop();

    cout << sf << endl;

    cout << sf.size() << endl;


    return 0;
}