# include "employeeTypeBoss.h"

// constructor implementation
EmployeeTypeBoss::EmployeeTypeBoss(int id, string name, int deptId) {
    this->id = id;
    this->name = name;
    this->deptId = deptId;
}

// destructor implementation
//EmployeeTypeBoss::~EmployeeTypeBoss() {}

// show info implementation
void EmployeeTypeBoss::showInfo() {
    cout << this->id << " " << this->name << " " << this->getDeptName() << endl;
}

// get department name implementation
string EmployeeTypeBoss::getDeptName() {
    return string("boss");
}
