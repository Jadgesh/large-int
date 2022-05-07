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

  friend std::istream& operator>>(std::istream&, LargeInt&); // Extraction overloading
  friend std::ostream& operator<<(std::ostream&, LargeInt&); // Insertion overloading

  private:
    DLList<int> data;
    bool isNeg;
  public:
    LargeInt(); // Default Constructor
    LargeInt(const int &); // Copy Constructor

    // Increment Overloading
    LargeInt operator++(int);

    // Operation Overloading
    LargeInt operator+(LargeInt&);
    LargeInt operator-(LargeInt&);
    LargeInt operator*(LargeInt&);
    // LargeInt operator/(LargeInt&);
    // LargeInt operator%(LargeInt&);

    // Conditional Overloading
    bool operator==(LargeInt&);
    bool operator>(LargeInt&);
    bool operator>=(LargeInt&);
    bool operator<(LargeInt&);
    bool operator<=(LargeInt&);
};
// class LargeInt{
//   private:
//     DLList<int> data;
//     bool negative;
//   public:
//     void setNegative(bool);
//     bool isNegative(){return negative;}
//     void insertDigit(int);
//     std::ostream& printData(std::ostream&);

//     // Copy Constructor
//     LargeInt(const int &);

//     // Extraction Overloading
//     friend std::istream& operator>>(std::istream&, LargeInt&);

//     // Insertion Overloading 
//     friend std::ostream& operator<<(std::ostream&, LargeInt&);

//     LargeInt operator=(const int&);
//     LargeInt operator++(int);
//     //Operation Overloading
//     LargeInt operator+(const int&);
//     LargeInt operator+(LargeInt&);
//     LargeInt operator-(LargeInt&);
//     // LargeInt operator*(LargeInt&);
//     // LargeInt operator/(LargeInt&);
//     // LargeInt operator%(LargeInt&);

//     // Conditional Overloading
//     bool operator==(LargeInt&);
//     bool operator>(LargeInt&);
//     bool operator>=(LargeInt&);
//     bool operator<(LargeInt&);
//     bool operator<=(LargeInt&);
// };

#endif