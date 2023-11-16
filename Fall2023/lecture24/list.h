// Singly Linked List

#ifndef _LIST_H_
#define _LIST_H_

#include <ostream>

using namespace std;

namespace ece220
{

// This is a templated linked list class
template <class T>
class List {
  private:
    // The ListNode class is private to the List class via the principle of encapsulation
    class ListNode {
      public:
        // Default ListNode constructor.
        ListNode() : next(NULL), data(T()) {}

        // Constructs a ListNode with the given data.
        ListNode(const T& ndata) : next(NULL), data(ndata) {}

        // A pointer to the next node in the list. May be NULL if one does not exist.
        ListNode* next;

        // The data contained in this node. 
        const T data;
    };

  public:
    // Default List constructor.
    List();

    // Copy constructor for a List.
    List(const List<T>& other);

    // Overloaded assignment operator for Lists.
    List<T>& operator=(const List<T>& rhs);

    // Destroys the current List.
    ~List();

    // Returns the size of the List.
    int size() const;

    // Determines if the current List is empty.
    bool empty() const;

    // Inserts a new node at the front of the List.
    void insertFront(const T& ndata);

    void removeFront();

    // Used to print the list.
    void print(ostream& os) const;

  private:
    // The head of the List. May be NULL if the List is empty.
    ListNode* head_;

    // The length of the current List. Do not forget to update it!
    int length_;

    // Copies the given list into the current list.
    void copy(const List<T>& other); 

    // Destroys all dynamically allocated memory associated with the current List class.
    void clear();

};

// needed for template instantiation
#include "list-inl.h"

}

#endif
