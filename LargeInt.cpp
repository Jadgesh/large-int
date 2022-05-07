#include "LargeInt.h"

// Start of Friend Functions

// TODO MAKE THIS CODE BETTER
std::istream& operator>>(std::istream& is, LargeInt& destination){
  destination.data.DestroyList();

  if(is.peek() == '-'){
    is.ignore();
    destination.isNeg = true;
  }

  while(isdigit(is.peek())){
    destination.data.insertAtStart(is.get() - '0');
  }

  if(is.peek() == ' ' || is.peek() == '\n')
    is.ignore();

  return is;
}

std::ostream& operator<<(std::ostream& os, LargeInt& source){
  if(source.isNeg)
    os << "-";

  for(DLListIterator<int> i = source.data.end(); i != source.data.preBegin(); --i)
    os << *i;
  
  return os;
}

// End of Friend Functions

// Constructors

LargeInt :: LargeInt(){
  isNeg = false;
  data.insert(0);
}

LargeInt :: LargeInt(const int &other){
  int temp = other;

  isNeg = temp < 0 ? true : false;
  
  while(temp != 0){
    data.insert(temp % 10);

    temp /= 10;
  }
}

LargeInt LargeInt :: operator++(int){
  LargeInt temp = 1;
  *this = *this + temp;
  return temp;
}

/***********************************************
 *        Start of Operation Overloading       *  
 ***********************************************/
LargeInt LargeInt :: operator+(LargeInt &other){
  LargeInt sum;
  // If both operands are the same sign, we can just add the digits
  // and keep the sign
  sum.data.DestroyList(); // Must call this because sum has a node already

  if(this->isNeg == other.isNeg){
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

    sum.isNeg = this->isNeg;
  }else{
    LargeInt negation;
    if(this->isNeg){
      // Lhand is negative
      negation = *this;
      negation.isNeg = false;

      sum = other - negation;
    }else{
      // Rhand is negative
      negation = other;
      negation.isNeg = false;

      sum = *this - negation;
    }
  }
  return sum;
}

LargeInt LargeInt :: operator-(LargeInt &other){
  LargeInt difference;

  difference.data.DestroyList(); // Makes sure difference is empty and removes the singular node

  if(this->isNeg == other.isNeg){
    LargeInt minuend = *this;
    LargeInt subtrahend = other;

    if(this->isNeg){
      subtrahend.isNeg = false;
      difference = minuend + subtrahend;
    }else{
      // a - b
      // minuend - subtrahend = difference

      // Assuming numbers are positive
      if(*this < other){
        minuend = other;
        subtrahend = *this;
        difference.isNeg = true;
      }else{
        difference.isNeg = false;
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
    if(this->isNeg){
      LargeInt negation = *this;
      negation.isNeg = false;

      difference = negation + other;

      difference.isNeg = true;
    }else{
      LargeInt negation = other;
      negation.isNeg = false;

      difference = *this + negation;

      difference.isNeg = false;
    }
  }

  return difference;
}

LargeInt LargeInt :: operator*(LargeInt &multiplier){
  LargeInt product;
  LargeInt temp = multiplier;
  std::cout << "Entered Multi\n";
  // Set sign
  if(this->isNeg || multiplier.isNeg)
    product.isNeg = true;

  temp.isNeg = false; // Toggle sign to make addition and looping easier

  for(LargeInt i = 0; i < temp; i++){
    product = product + *this;
  }

  return product;
}
/***********************************************
 *         End of Operation Overloading        *  
 ***********************************************/


/***********************************************
 *       Start of Conditional Overloading      *
 ***********************************************/
bool LargeInt :: operator==(LargeInt& other){
  if(this->isNeg == other.isNeg && this->data.length() == other.data.length()){
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
  if(this->isNeg == other.isNeg){
    if(this->data.length() == other.data.length()){
      // Loop through each comparing each digit from this to other. If the current digit from this is
      // ever greater than other's digit then return true. If we reach the end of the loop then return false
      DLListIterator<int> thisIterator = this->data.end();
      DLListIterator<int> otherIterator = other.data.end();

      while(thisIterator != this->data.preBegin()){
        if((this->isNeg && *thisIterator < *otherIterator) || (!this->isNeg && *thisIterator > *otherIterator))
          return true;
        --thisIterator;
        --otherIterator;
      }
    }else{
      // Different length
      if(this->isNeg && this->data.length() < other.data.length() || !this->isNeg && this->data.length() > other.data.length())
        return true;
    }
  }else if(!this->isNeg)
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
  if(this->isNeg == other.isNeg){
    if(this->data.length() == other.data.length()){
      // Loop through each comparing each digit from this to other. If the current digit from this is
      // ever less than other's digit then return true. If we reach the end of the loop then return false
      DLListIterator<int> thisIterator = this->data.end();
      DLListIterator<int> otherIterator = other.data.end();

      while(thisIterator != this->data.preBegin()){
        if((this->isNeg && *thisIterator > *otherIterator) || (!this->isNeg && *thisIterator < *otherIterator))
          return true;
        --thisIterator;
        --otherIterator;
      }
    }else{
      // Different length
      if(this->isNeg && this->data.length() > other.data.length() || !this->isNeg && this->data.length() < other.data.length())
        return true;
    }
  }else if(this->isNeg)
    return true;

  return false;
}

// this <= other
bool LargeInt :: operator<=(LargeInt &other){
  if(*this < other || *this == other)
    return true;
  return false;
}

/***********************************************
 *        End of Conditional Overloading       *
 ***********************************************/