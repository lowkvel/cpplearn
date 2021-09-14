# include "employeeTypeNormal.h"

// constructor implementation
EmployeeTypeNormal::EmployeeTypeNormal(int id, string name, int deptId) {
    this->id = id;
    this->name = name;
    this->deptId = deptId;
}

// destructor implementation
//EmployeeTypeNormal::~EmployeeTypeNormal() {}

// show info implementation
void EmployeeTypeNormal::showInfo() {
    cout << this->id << " " << this->name << " " << this->getDeptName() << endl;
}

// get department name implementation
string EmployeeTypeNormal::getDeptName() {
    return string("normal");
}
