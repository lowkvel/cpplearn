# include <iostream>

# include "employeeManager.h"
# include "employeeType.h"
# include "employeeTypeNormal.h"
# include "employeeTypeManager.h"
# include "employeeTypeBoss.h"

using namespace std;

void main_func();
void test_employee_type();

// build command:
// /usr/bin/clang++ -std=c++11 -g employeeManagementSystem.cpp employeeManager.cpp employeeType.cpp employeeTypeNormal.cpp employeeTypeManager.cpp employeeTypeBoss.cpp -o employeeManagementSystem
/*
employeeManager.cpp employeeType.cpp employeeTypeNormal.cpp employeeTypeManager.cpp employeeTypeBoss.cpp
*/

int main() {

    // main function
    main_func();

    // tester
    //test_employee_type();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void main_func() {
    // instantiate a employeeManager object em
    EmployeeManager em;

    int choice = 0;
    while (true) {
        // show menu and get selected choice
        em.showMenu();
        cout << "input your choice: " << endl;
        cin >> choice;

        // switch choices
        switch (choice) {
            case 0:     // quit
                em.quit();
                break;
            case 1:     // add
                em.add();
                break;
            case 2:     // show
                em.show();
                break;
            case 3:     // delete
                em.del();
                break;
            case 4:     // modify
                em.modify();
                break;
            case 5:     // find
                em.find();
                break;
            case 6:     // sort
                em.sort();
                break;
            case 7:     // clear
                break;
            default:    // clear screen
                system("clear");
                break;
        }
    }
}

void test_employee_type () {
    EmployeeType *normal = new EmployeeTypeNormal(1, "Ada", 1);
    normal->showInfo();
    delete normal;

    EmployeeType *manager = new EmployeeTypeManager(2, "Bob", 2);
    manager->showInfo();
    delete manager;

    EmployeeType *boss = new EmployeeTypeBoss(3, "Clara", 3);
    boss->showInfo();
    delete boss;
}
