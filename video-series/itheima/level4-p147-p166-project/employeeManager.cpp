# include "employeeManager.h"

// constructor implementation
EmployeeManager::EmployeeManager() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    switch (this->checkFileStatus(ifs)) {
        case 0:
            cout << "file not exist" << endl;
            this->employeeCount = 0;
            this->empArray = NULL;
            this->fileIsEmpty = true;
            break;
        case 1:
            cout << "file is empty" << endl;
            this->employeeCount = 0;
            this->empArray = NULL;
            this->fileIsEmpty = true;
            break;
        case 2:
            cout << "file is read" << endl;
            this->employeeCount = this->get_employeeCount();
            this->empArray = new EmployeeType *[this->employeeCount];
            this->init_employee();
            break;
        default:
            this->employeeCount = 0;
            this->empArray = NULL;
            this->fileIsEmpty = true;
            break;
    }
    ifs.close();
}

// destructor implementation
EmployeeManager::~EmployeeManager() {
    if (this->empArray != NULL) {
        delete[] this->empArray;
        this->empArray = NULL;
    }
}

// read file
void EmployeeManager::read() {

}

// save file
void EmployeeManager::save() {
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    for (int i = 0; i < this->employeeCount; i++) {
        ofs << this->empArray[i]->id << " "
            << this->empArray[i]->name << " "
            << this->empArray[i]->deptId << endl;
    }

    ofs.close();
}

// check if the file is empty or not exist
int EmployeeManager::checkFileStatus(ifstream &ifs) {
    if (!ifs.is_open())     // file not exist
        return 0;
    else {                  // file exist but is empty
        char ch;
        ifs >> ch;
        if (ifs.eof())
            return 1;
    }
    return 2;               // file exist and with data in it
}

// get employee count
int EmployeeManager::get_employeeCount() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int deptId;
    
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> deptId) 
        num++;

    ifs.close();

    return num;
}

// init employee
void EmployeeManager::init_employee() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int deptId;

    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> deptId) {
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
        this->empArray[index] = emp;
        index++;
    }

    ifs.close();
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

        // save to file, comment
        this->save();
        this->fileIsEmpty = false;
        cout << count << " employees added" << endl;

        system("clear");
    } else {
        cout << "wrong input" << endl;
    }
}
