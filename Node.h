#ifndef NODE_H
#define NODE_H

#include <iostream> // Allows usage of NULL and nullptr

template<class T>
struct Node{
  T data;
  Node<T> *prev;
  Node<T> *next;
  Node(T val = NULL , Node<T> *p = nullptr, Node<T> *n = nullptr) : data(val), prev(p), next(n){}
  ~Node(){
    data = (T)NULL;
    prev = nullptr;
    next = nullptr;
  }
};
#endif