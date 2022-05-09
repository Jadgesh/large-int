#ifndef LARGEINT_H
#define LARGEINT_H

#include <iostream> // For extraction and insertion overloading
#include <string>
#include "DLList.cpp"
#include "DLListIterator.h"

/* ----------------------------------------
 * |                 ToDo                 |
 * ----------------------------------------
 * | Status |          Function           |
 * ----------------------------------------
 * |    x   | Addition (+)                |
 * |    x   | Subtraction (-)             |
 * |    x   | Multiplication (*)          |
 * |    x   | Division (/)                |
 * |    x   | Modulus (%)                 |
 * |    ✓   | Equality (==)               |
 * |    ✓   | Less than (<)               |
 * |    ✓   | Less than equals to (<=)    |
 * |    ✓   | Greater than (>)            |
 * |    ✓   | Greater than equals to (>=) |
 * |    ✓   | Insertion (<<)              |
 * |    ✓   | Extraction (>>)             |
 * ---------------------------------------- */

class LargeInt{

  friend std::ostream& operator<<(std::ostream&, LargeInt&); // Insertion overloading
  friend std::istream& operator>>(std::istream&, LargeInt&); // Extraction overloading

  private:
    DLList<int> data;
    bool isNeg;
    bool isZero;
  public:
    LargeInt();
    LargeInt(const int &);

    void insertDigit(int, bool);
    
    LargeInt operator++();

    // Operation Overloading
    LargeInt operator+(LargeInt&);
    LargeInt operator-(LargeInt&);
    LargeInt operator*(LargeInt&);
    LargeInt operator/(LargeInt&);

    // Conditional Overloading
    bool operator==(LargeInt&);
    bool operator>(LargeInt&);
    bool operator>=(LargeInt&);
    bool operator<(LargeInt&);
    bool operator<=(LargeInt&);

    void toggleIsZero();

  // private:
  //   DLList<int> data;
  //   bool isNeg;
  // public:
  //   LargeInt(); // Default Constructor
  //   LargeInt(const int &); // Copy Constructor

  //   // Increment Overloading
  //   LargeInt operator++(int);

  //   LargeInt operator*(LargeInt&);
  //   // LargeInt operator/(LargeInt&);
  //   // LargeInt operator%(LargeInt&);
};
#endif