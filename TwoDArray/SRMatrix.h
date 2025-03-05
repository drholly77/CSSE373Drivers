// SRMatrix.h
#pragma once
#include "Wrapper.h"
#include "StaticArray\StaticArray1.hpp"


 // ----------------------------------------------
 // Create StudentRecord
 // ----------------------------------------------

class StudentRecord {
public:
    Text name, major, studentId;
    Integer age;

    void transferFrom(StudentRecord& source) { 
       name.transferFrom(source.name);
       major.transferFrom(source.major);
       studentId.transferFrom(source.studentId);
       age.transferFrom(source.age);
    }; 

    friend ostream& operator << (ostream& os, StudentRecord& r) {
       os << "(" << r.name<< "," << r.major << "," << r.studentId << "," << r.age << ")";
       return os;
    }; 
 };

 // ----------------------------------------------
 // Create Two Dimensional Matrix of StudentRecord
 // ----------------------------------------------

enum {columnLower = 0, columnUpper = 9, maxColumns = 10};
enum {rowLower = 0, rowUpper = 14, maxRows = 15};

 // 1st Create Columns 
typedef StaticArray1 <StudentRecord, columnLower, columnUpper> ColumnArray;

 // 2nd Create Rows by plugging ColumnArray into StaticArray
typedef StaticArray1 <ColumnArray, rowLower, rowUpper> MatrixOfStudents;
