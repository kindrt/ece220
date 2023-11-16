// Singly Linked List

#ifndef _STACK_H_
#define _STACK_H_

#include <ostream>
#include "list.h"

using namespace std;

namespace ece220
{

template <class T>
class Stack : public List<T> { 
    public:
        void push(const T& ndata);
        void pop();
};

template <class T>
void Stack<T>::push(T const& ndata) {
    this->insertFront(ndata);
}

template <class T>
void Stack<T>::pop() {
    this->removeFront();
}

}

#endif