#include "largeint.h"

void LargeInt :: insertDigit(int digit){
  data.insertAtStart(digit);
}

void LargeInt :: setNegative(bool val){
  negative = val;
}

std::ostream& LargeInt :: printData(std::ostream& os){
  if(negative)
    os << "-";

  for(DLListIterator<int> i = data.end(); i != data.preBegin(); --i){
    os << *i;
  }

  return os;
}

std::istream& operator>>(std::istream& is, LargeInt& destination){
  if(is.peek() == '-'){
    is.ignore();
    destination.setNegative(true);
  }else
    destination.setNegative(false);

  while(isdigit(is.peek())){
    destination.insertDigit(is.get() - '0');
  }

  if(is.peek() == ' ' || is.peek() == '\n')
    is.ignore();

  return is;
}

std::ostream& operator<<(std::ostream& os, LargeInt& source){
  source.printData(os);
  return os;
}

// Comparison Overloading

bool LargeInt :: operator==(LargeInt& other){
  if(this->isNegative() == other.isNegative() && this->data.length() == other.data.length()){
    DLListIterator<int> thisIterator = this->data.begin();
    DLListIterator<int> otherIterator = other.data.begin();

    while(thisIterator != this->data.postEnd()){
      if(*thisIterator != *otherIterator)
        return false;
      
      ++thisIterator;
      ++otherIterator;
    }

    return true;
  }else
    return false;
}

// this > other
bool LargeInt :: operator>(LargeInt& other){
  // If both LargeInt(s) have the same sign (either positive or negative) and they have the
  // same number of digits, there's no way to know which one is greater without looping through
  // each digit and comparing them
  if(this->isNegative() == other.isNegative()){
    if(this->data.length() == other.data.length()){
      // Loop through each comparing each digit from this to other. If the current digit from this is
      // ever greater than other's digit then return true. If we reach the end of the loop then return false
      DLListIterator<int> thisIterator = this->data.end();
      DLListIterator<int> otherIterator = other.data.end();

      while(thisIterator != this->data.preBegin()){
        if((this->isNegative() && *thisIterator < *otherIterator) || (!this->isNegative() && *thisIterator > *otherIterator))
          return true;
        --thisIterator;
        --otherIterator;
      }
    }else{
      // Different length
      if(this->isNegative() && this->data.length() < other.data.length() || !this->isNegative() && this->data.length() > other.data.length())
        return true;
    }
  }else if(!this->isNegative())
    return true;

  return false;
}

// this >= other
bool LargeInt :: operator>=(LargeInt &other){
  if(*this > other || *this == other)
    return true;
  return false;
}

// this < other
bool LargeInt :: operator<(LargeInt& other){
  // If both LargeInt(s) have the same sign (either positive or negative) and they have the
  // same number of digits, there's no way to know which one is less without looping through
  // each digit and comparing them
  if(this->isNegative() == other.isNegative()){
    if(this->data.length() == other.data.length()){
      // Loop through each comparing each digit from this to other. If the current digit from this is
      // ever less than other's digit then return true. If we reach the end of the loop then return false
      DLListIterator<int> thisIterator = this->data.end();
      DLListIterator<int> otherIterator = other.data.end();

      while(thisIterator != this->data.preBegin()){
        if((this->isNegative() && *thisIterator > *otherIterator) || (!this->isNegative() && *thisIterator < *otherIterator))
          return true;
        --thisIterator;
        --otherIterator;
      }
    }else{
      // Different length
      if(this->isNegative() && this->data.length() > other.data.length() || !this->isNegative() && this->data.length() < other.data.length())
        return true;
    }
  }else if(this->isNegative())
    return true;

  return false;
}

// this <= other
bool LargeInt :: operator<=(LargeInt &other){
  if(*this < other || *this == other)
    return true;
  return false;
}


// Operator Overloading
LargeInt LargeInt :: operator+(LargeInt &other){
  LargeInt sum;
  
  return sum;
}

// LargeInt LargeInt :: operator-(LargeInt &other){
  
// }

// LargeInt LargeInt :: operator*(LargeInt &other){
  
// }

// LargeInt LargeInt :: operator/(LargeInt &other){
  
// }

// LargeInt LargeInt :: operator%(LargeInt &other){
  
// }