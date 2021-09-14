# pragma once

# include <iostream>
# include "employeeType.h"

using namespace std;

class EmployeeTypeManager: public EmployeeType {
public:
    // constructor
    EmployeeTypeManager(int id, string name, int deptId);

    // destructor
    //~EmployeeTypeManager();

    // show info
    virtual void showInfo();

    // get department name
    virtual string getDeptName();
};
