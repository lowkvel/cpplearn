#include <iostream>

#include "employeeManager.h"

using namespace std;

// build command:
// /usr/bin/clang++ -std=c++11 -g employeeManagementSystem.cpp employeeManager.cpp -o employeeManagementSystem

int main() {

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
                break;
            case 3:     // show
                break;
            case 4:     // modify
                break;
            case 5:     // find
                break;
            case 6:     // sort
                break;
            case 7:     // clear
                break;
            default:    // clear screen
                system("clear");
                break;
        }
    }

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}
