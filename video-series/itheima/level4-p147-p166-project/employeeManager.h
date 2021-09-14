# pragma once

# include <iostream>
# include "employeeType.h"
# include "employeeTypeNormal.h"
# include "employeeTypeManager.h"
# include "employeeTypeBoss.h"

using namespace std;

class EmployeeManager {
public:
    int employeeCount;          // employee count
    EmployeeType ** empArray;     // ?

public:
    // constructor
    EmployeeManager();

    // destructor
    ~EmployeeManager();

    // show menu
    void showMenu();

    // 0. quit
    void quit();

    // 1. add
    void add();
};
