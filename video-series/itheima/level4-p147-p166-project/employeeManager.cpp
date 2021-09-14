# include "employeeManager.h"

// constructor implementation
EmployeeManager::EmployeeManager() {
    this->employeeCount = 0;
    this->empArray = NULL;
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

// 1. add implementation
void EmployeeManager::add() {

    // get the number of employee to add
    int count = 0;
    cout << "input the number of employee to add: " << endl; cin >> count; 

    if (count > 0) {
        // calculate the memory space required for old+new employees, then allocate it
        int newSize = this->employeeCount + count;
        EmployeeType ** newEmpArray = new EmployeeType*[newSize];

        // relocate existing employees to new array
        if (this->empArray != NULL) 
            for (int i = 0; i < this->employeeCount; i++)
                newEmpArray[i] = this->empArray[i];
        
        // add new employees to new space
        for (int i = 0; i < count; i++) {
            // get details
            cout << i << " : " << endl;
            int id;         cout << "input id: " << endl;       cin >> id;
            string name;    cout << "input name: " << endl;     cin >> name;
            int deptId;     cout << "input dept id (1:normal; 2:manager; 3:boss): " << endl;    cin >> deptId;

            // create new EmployeeType objects according to dept id
            EmployeeType *emp = NULL;
            switch (deptId) {
                case 1:
                    emp = new EmployeeTypeNormal(id, name, deptId);
                    break;
                case 2:
                    emp = new EmployeeTypeManager(id, name, deptId);
                    break;
                case 3:
                    emp = new EmployeeTypeBoss(id, name, deptId);
                    break;
                default:
                    break;
            }

            // add it
            newEmpArray[this->employeeCount + i] = emp;
        }

        // delete old memory space and re-direct to new one
        delete[] this->empArray;
        this->empArray = newEmpArray;

        // update employee count
        this->employeeCount = newSize;

        // comment
        cout << count << " employees added" << endl;
        system("clear");
    } else {
        cout << "wrong input" << endl;
    }
}
