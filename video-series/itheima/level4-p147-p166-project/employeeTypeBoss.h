# pragma once

# include <iostream>
# include "employeeType.h"

using namespace std;

class EmployeeTypeBoss: public EmployeeType {
public:
    // constructor
    EmployeeTypeBoss(int id, string name, int deptId);

    // destructor
    //~EmployeeTypeBoss();

    // show info
    virtual void showInfo();

    // get department name
    virtual string getDeptName();
};
