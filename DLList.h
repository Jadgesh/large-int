#ifndef DLLIST_H
#define DLLIST_H

#include <iostream>
#include <string>

#include "Node.h"
#include "DLListIterator.cpp"

template<class T>
class DLList{
  private:
    Node<T> *first; // Hold the head/first node
    Node<T> *last; // Holds the tail/last node
    int _length; // Holds the length of our list


  public:
    DLList(); // Constructor
    ~DLList(); // Deconstructor
    void DestroyList();

    void init(); // Initializes our default values

    DLList(const DLList<T> &); // Copy Constructor
    DLList<T>& operator=(const DLList<T>& other); // Assignment overloading

    void copy(const DLList<T> &); // copys from one list to current list

    int length(); // Returns the length of our list
    bool isEmpty(); // Returns if our list is empty

    void insert(T); // Insert an item at the end of the list
    void insertAtStart(T); // Insert an item at the start of the list
    bool searchFor(T); // Search for an item and return if it's apart of our list
    bool remove(T); // Remove the first occurence of an item from the list

    // Iterator methods
    DLListIterator<T> begin(); // Returns an iterator of the first node
    DLListIterator<T> end(); // Returns an iterator of the last node

    DLListIterator<T> preBegin();
    DLListIterator<T> postEnd();

};
#endif