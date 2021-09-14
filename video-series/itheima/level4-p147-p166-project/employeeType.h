#pragma once

#include <iostream>

using namespace std;

// this is a virtual class, no need for implementation (*.cpp can be empty or deleted)
class EmployeeType {
public:
    int id;         // employee id
    string name;    // employee name
    int deptId;     // employee department id

    // virtual destructor
    virtual ~EmployeeType() {}

    // pure virtual funcs
    virtual void showInfo() = 0;        // show info
    virtual string getDeptName() = 0;   // get department name
};
