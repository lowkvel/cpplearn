# pragma once

# include <iostream>
# include "employeeType.h"

using namespace std;

class EmployeeTypeNormal: public EmployeeType {
public:
    // constructor
    EmployeeTypeNormal(int id, string name, int deptId);

    // destructor
    //~EmployeeTypeNormal();

    // show info
    virtual void showInfo();

    // get department name
    virtual string getDeptName();
};
