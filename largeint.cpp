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
  // If both operands are the same sign, we can just add the digits
  // and keep the sign
  if(this->isNegative() == other.isNegative()){
    DLListIterator<int> thisIterator = this->data.begin();
    DLListIterator<int> otherIterator = other.data.begin();

    bool carry = false;
    while(thisIterator != this->data.postEnd() && otherIterator != other.data.postEnd()){
      int val = *thisIterator + *otherIterator;

      if(carry)
        val++;

      carry = val > 9 ? true : false;
      sum.data.insert(val%10);
      
      ++thisIterator;
      ++otherIterator;
    }

    while(thisIterator != this->data.postEnd()){
      int val = *thisIterator;

      if(carry)
        val++;

      carry = val > 9 ? true : false;

      sum.data.insert(val%10);
      
      ++thisIterator;
    }

    while(otherIterator != other.data.postEnd()){
      int val = *otherIterator;

      if(carry)
        val++;

      carry = val > 9 ? true : false;

      sum.data.insert(val%10);
      
      ++otherIterator;
    }

    if(carry)
      sum.data.insert(1);

    sum.setNegative(this->isNegative());
  }else{
    LargeInt negation;
    if(this->isNegative()){
      // Lhand is negative
      negation = *this;
      negation.setNegative(false);

      sum = other - negation;
    }else{
      // Rhand is negative
      negation = other;
      negation.setNegative(false);

      sum = *this - negation;
    }
  }
  return sum;
}

LargeInt LargeInt :: operator-(LargeInt &other){
  LargeInt difference;
  if(this->isNegative() == other.isNegative()){
    LargeInt minuend = *this;
    LargeInt subtrahend = other;

    if(this->isNegative()){
      subtrahend.setNegative(false);
      difference = minuend + subtrahend;
    }else{
      // a - b
      // minuend - subtrahend = difference

      // Assuming numbers are positive
      if(*this < other){
        minuend = other;
        subtrahend = *this;
        difference.setNegative(true);
      }else{
        difference.setNegative(false);
      }

      DLListIterator<int> mItr = minuend.data.begin();
      DLListIterator<int> sItr = subtrahend.data.begin();

      bool borrow = false;
      while(mItr != minuend.data.postEnd() && sItr != subtrahend.data.postEnd()){
        int val = *mItr;

        if(borrow)
          val--;

        borrow = false;

        if(*sItr > val){
          borrow = true; // We need to borrow
          val += 10;
        }

        val -= *sItr;

        difference.data.insert(val);

        ++mItr;
        ++sItr;
      }
    }

  }else{
    if(this->isNegative()){
      LargeInt negation = *this;
      negation.setNegative(false);

      difference = negation + other;

      difference.setNegative(true);
    }else{
      LargeInt negation = other;
      negation.setNegative(false);

      difference = *this + negation;

      difference.setNegative(false);
    }
  }

  return difference;
}

// LargeInt LargeInt :: operator*(LargeInt &other){
  
// }

// LargeInt LargeInt :: operator/(LargeInt &other){
  
// }

// LargeInt LargeInt :: operator%(LargeInt &other){
  
// }