#ifndef DLLISTITERATOR_H
#define DLLISTITERATOR_H

#include "Node.h"
#include <iostream> // Allows usage of NULL and nullptr

template <class T>
class DLListIterator{
  private:
    Node<T> *cur;
  public:
    DLListIterator();
    DLListIterator(Node<T> *); // Constructor
    T operator*();
    DLListIterator<T>& operator++();
    DLListIterator<T>& operator--();
    bool operator==(const DLListIterator<T>&) const;
    bool operator!=(const DLListIterator<T>&) const;
};
#endif