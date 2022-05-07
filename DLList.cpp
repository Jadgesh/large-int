#include "DLList.h"

template <class T>
DLList<T> :: DLList(){
  init();
}

template <class T>
void DLList<T> :: init(){
  first = nullptr;
  last = nullptr;
  _length = 0;
}

template <class T>
DLList<T> :: ~DLList(){
  DestroyList();
}

template <class T>
void DLList<T> :: DestroyList(){
  if(!isEmpty()){
    Node<T> *p = first->next;

    // Delete all nodes excluding the last node
    while(p != nullptr){
      delete(p->prev);
      p = p->next;
    }

    delete(last);

    first = nullptr;
    last = nullptr;

    _length = 0;
  }
}
template <class T>
DLList<T> :: DLList(const DLList<T> &other){
  init();
  copy(other);
}

template <class T>
DLList<T>& DLList<T> :: operator=(const DLList<T>& other){
  // if we're doing an operation similar to a = a
  // just return a
  if(this == &other)
    return *this;
  else{
    init();
    copy(other);
  }
  return *this; // Return this so we can perform operations like
                // (a = b).print(); prints the list of a 
}

template <class T>
void DLList<T> :: copy(const DLList<T>& other){
  Node<T> *p = other.first;

    while(p != nullptr){
      insert(p->data);
      p = p->next;
    }
}

/*
 * Returns the length of our list
 */
template <class T>
int DLList<T> :: length(){
  return _length;
}

/*
 * Returns a boolean value representing if the list is empty or not
 */
template <class T>
bool DLList<T> :: isEmpty(){
  return _length == 0;
}

/*
 * Inserts a node with user provided data at the end of our Doubley Linked List
 *
 * @param data the data that will be stored in the new node
 */
template <class T>
void DLList<T> :: insert(T data){
  // If there's no nodes in our list we need to handle adding that node a bit differently
  if(isEmpty()){
    // We initialize the node with data only as next and prev don't point to anything
    Node<T> *p = new Node<T>(data);
    // We update the first and last node pointer for our list to the single node in our list
    first = p;
    last = p;
  }else{
    // Initialize a node with our data and link to the previous last node
    Node<T> *p = new Node<T>(data, last);
    // Link the previous last node's next to our new last node
    last->next = p;
    // Update the pointer for our last node
    last = p;
  }
  // Increase our tally for amount of nodes in our list
  _length++;
}

/*
 * Inserts a node at the start of our list
 *
 * @param data is the data our new node will contain
 */
template <class T>
void DLList<T> :: insertAtStart(T data){
  // If there's no nodes in our list we need to handle adding that node a bit differently
  if(isEmpty()){
    // We initialize the node with data only as next and prev don't point to anything
    Node<T> *p = new Node<T>(data);
    // We update the first and last node pointer for our list to the single node in our list
    first = p;
    last = p;
  }else{
    //Init our new node with user provided data and link the next field to
    // our current first node
    Node<T> *p = new Node<T>(data, nullptr, first);
    // Update the old first node to point to our new first node
    first->prev = p;
    // Update which node is first
    first = p;
  }
  // increase the counter for # of nodes in our list
  _length++;
}

/*
 * Searches for specific data and returns true if found and false if not
 *
 * @param target the data we're searching for
 */
template <class T>
bool DLList<T> :: searchFor(T target){
  Node<T> *p = first;
  while(p != nullptr){
    // If the node we're currently at contains the information we're looking for
    // return true immediately
    if(p->data == target){
      return true;
    }
    p = p->next;
  }
  // If we exit the loop, then we've reached the end of the list and we
  // didn't find the target
  return false;
}

/*
 * Searches for and removes the first occurence of specific data
 *
 * @param target the data we're looking to remove 
 */
template <class T>
bool DLList<T> :: remove(T target){

  // If our list is empty, do nothing. There's nothing we can remove
  if(!isEmpty()){
    // Find node
    Node<T> *p = first;
    // Walk through our list until we reach the end of the list or
    // we find our target data
    while(p->data != target && p->next != nullptr)
      p = p->next;
    
    // Check if the node we're at is the data we're looking for
    // If it's not then we reached the end of the list and can exit the function
    // There's nothing to delete
    if(p->data == target){
      // Special cases for removal occur when the node is our first node or our last node
      if(p == first){
        // Point our first node to the next node 
        first = p->next;

        // If our list is greater than one we can update first previous
        // If it's not, then we'll get a segmentation fault because
        // there's no node->prev to update
        if(_length > 1)
          first->prev = nullptr;

        // Finally delete p
        delete p;
      }else if(p == last){
        // If the node we're deleting is our last node, we need to point last to the previous node
        // and set that node's next node to nullptr
        // NOTE* We don't need to check length because we'll never enter this block of code
        //       when we have a single node that's the target as that case would execute the p==first block
        last = p->prev;
        last->next = nullptr;

        delete p;
      }else{
        // If the node is in the middle then we need to update the previous node's next field to point to the next node
        // and we need to update the next node's previous field to point to the previous node
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
      }
      // Decrement our length to correctly represent the amount of nodes we have 
      _length--;
      return true;
    }else
      return false;
  }
  return false;
}

template <class T>
DLListIterator<T> DLList<T> :: begin(){
  DLListIterator<T> temp(first);
  return temp;
}

template <class T>
DLListIterator<T> DLList<T> :: preBegin(){
  DLListIterator<T> temp(first->prev);
  return temp;
}

template <class T>
DLListIterator<T> DLList<T> :: end(){
  DLListIterator<T> temp(last);
  return temp;
}

template <class T>
DLListIterator<T> DLList<T> :: postEnd(){
  DLListIterator<T> temp(last->next);
  return temp;
}