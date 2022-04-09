#include "DLListIterator.h"

template <class T>
DLListIterator<T> :: DLListIterator() : cur(nullptr){}

template <class T>
DLListIterator<T> :: DLListIterator(Node<T> *ptr) : cur(ptr){}

template <class T>
T DLListIterator<T> :: operator*(){
  return cur->data;
}

template <class T>
DLListIterator<T>& DLListIterator<T> :: operator++(){
  cur = cur->next;
  return *this;
}

template <class T>
DLListIterator<T>& DLListIterator<T> :: operator--(){
  cur = cur->prev;
  return *this;
}

template <class T>
bool DLListIterator<T> :: operator==(const DLListIterator<T>& rVal) const{
  return (cur == rVal.cur);
}

template <class T>
bool DLListIterator<T> :: operator!=(const DLListIterator<T>& rVal) const{
  return (cur != rVal.cur);
} 