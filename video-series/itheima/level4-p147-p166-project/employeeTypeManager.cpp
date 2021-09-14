# include "employeeTypeManager.h"

// constructor implementation
EmployeeTypeManager::EmployeeTypeManager(int id, string name, int deptId) {
    this->id = id;
    this->name = name;
    this->deptId = deptId;
}

// destructor implementation
//EmployeeTypeManager::~EmployeeTypeManager() {}

// show info implementation
void EmployeeTypeManager::showInfo() {
    cout << this->id << " " << this->name << " " << this->getDeptName() << endl;
}

// get department name implementation
string EmployeeTypeManager::getDeptName() {
    return string("manager");
}
