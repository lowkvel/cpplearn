#include "employeeManager.h"

// constructor implementation
EmployeeManager::EmployeeManager() {

}

// destructor implementation
EmployeeManager::~EmployeeManager() {

}

// show menu implementation
void EmployeeManager::showMenu() {
    cout << "***********" << endl;
    cout << " 0. quit" << endl;
    cout << " 1. add" << endl;
    cout << " 2. show" << endl;
    cout << " 3. delete" << endl;
    cout << " 4. modify" << endl;
    cout << " 5. find" << endl;
    cout << " 6. sort" << endl;
    cout << " 7. clear" << endl;
    cout << "***********" << endl;
}

// 0. quit implementation
void EmployeeManager::quit() {
    cout << "quitted" << endl;
    exit(0);
}
