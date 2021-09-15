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
            this->fileIsEmpty = false;
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

        //system("clear");
    } else {
        cout << "wrong input" << endl;
    }
}

// 2. show implementation
void EmployeeManager::show() {
    if (this->fileIsEmpty)
        cout << "file does not exist or is empty" << endl;
    else
        for (int i = 0; i < this->employeeCount; i++)
            this->empArray[i]->showInfo();
    //system("clear");
}

// get index of an employee given specific employee id implementation
int EmployeeManager::getIndex(int id) {
    for (int i = 0; i < this->employeeCount; i++)
        if (this->empArray[i]->id == id)
            return i;
    return -1;
}

/* todo
int EmployeeManager::getIndex(int getway) {
    switch (getway) {
        case 1:     // employee id
            break;
        case 2:     // employee name
            break;
        case 3:     // employee department id
            break;
        default:
            break;
    }
    return -1;
}
*/

// 3. delete implementation
void EmployeeManager::del() {
    if (this->fileIsEmpty) 
        cout << "file does not exist or is empty" << endl;
    else {
        // cin the id needed
        int id = -1;
        cout << "input employee id to delete: " << endl;
        cin >> id;

        // get index of the id
        int index = this->getIndex(id);
        if (index == -1)
            cout << "employee with id " << id << " does not exist" << endl;
        else {
            // delete it and modify employee count
            for (int i = index; i < this->employeeCount - 1; i++)
                this->empArray[i] = this->empArray[i + 1];
            this->employeeCount--;

            // save file
            this->save();
            cout << "delete successful" << endl;
        }
    }
}

// 4. modify implementation
void EmployeeManager::modify() {
    if (this->fileIsEmpty) 
        cout << "file does not exist or is empty" << endl;
    else {
        // cin the id needed
        int id = -1;
        cout << "input employee id to modify: " << endl;
        cin >> id;

        // get index of the id
        int index = this->getIndex(id);
        if (index == -1)
            cout << "employee with id " << id << " does not exist" << endl;
        else {
            // delete the element in heap pool, but keep the pointer
            delete this->empArray[index];

            // get new infomation
            int id;         cout << "input id: " << endl;       cin >> id;
            string name;    cout << "input name: " << endl;     cin >> name;
            int deptId;     cout << "input dept id (1:normal; 2:manager; 3:boss): " << endl;    cin >> deptId;

            // create new EmployeeType object according to dept id
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

            // redirect to the newly created employee object
            this->empArray[index] = emp;

            // save file
            this->save();
            cout << "modify successful" << endl;
        }
    }
}

// 5. find implementation
void EmployeeManager::find() {
    if (this->fileIsEmpty) 
        cout << "file does not exist or is empty" << endl;
    else {
        // cin the find method needed
        int find_method = -1;
        cout << "input find method(1. id; 2. name; 3. dept id): " << endl;
        cin >> find_method;

        switch (find_method) {
            case 1: {
                // cin the id needed
                int id = -1;
                cout << "input employee id to find: " << endl;
                cin >> id;

                // get index of the id, and display the result
                int index = this->getIndex(id);
                if (index == -1)
                    cout << "employee with id " << id << " does not exist" << endl;
                else
                    this->empArray[index]->showInfo();

                break;
            }
            case 2: {
                // cin the name needed
                string name = "";
                cout << "input employee name to find: " << endl;
                cin >> name;

                // get indexes of the name, and display the result
                bool flag = false;
                for (int i = 0; i < this->employeeCount; i++) 
                    if (this->empArray[i]->name == name) {
                        flag = true;
                        this->empArray[i]->showInfo();
                    }
                if (flag == false) {
                    cout << "employee with name " << name << " does not exist" << endl;
                }

                break;
            }
            case 3: {
                // cin the dept id needed
                int deptId = 0;
                cout << "input employee dept id to find: " << endl;
                cin >> deptId;

                // get indexes of the dept id, and display the result
                bool flag = false;
                for (int i = 0; i < this->employeeCount; i++) 
                    if (this->empArray[i]->deptId == deptId) {
                        flag = true;
                        this->empArray[i]->showInfo();
                    }
                if (flag == false) {
                    cout << "employee with dept Id " << deptId << " does not exist" << endl;
                }

                break;
            }
            default:
                break;
        }
    }
}

// 6. sort implementation
void EmployeeManager::sort() {
    if (this->fileIsEmpty) 
        cout << "file does not exist or is empty" << endl;
    else {
        // cin the sorting attribute needed
        int selected = 0;
        cout << "input sorting attribute to sort (1: id; 2: name; 3: dept id): " << endl;
        cin >> selected;

        // select sort
        for (int i = 0; i < this->employeeCount; i++) {
            int index = i;
            for (int j = i + 1; j < this->employeeCount; j++)
                switch (selected) {
                    case 1:
                        if (this->empArray[index]->id > this->empArray[j]->id)
                            index = j;
                        break;
                    case 2:
                        if (this->empArray[index]->name > this->empArray[j]->name)
                            index = j;
                        break;
                    case 3:
                        if (this->empArray[index]->deptId > this->empArray[j]->deptId)
                            index = j;
                        break;
                    default:
                        break;
                }

            // swap
            if (i != index) {
                EmployeeType *temp = this->empArray[i];
                this->empArray[i] = this->empArray[index];
                this->empArray[index] = temp;
            }
        }
        
        // save file
        this->save();
        cout << "sort successful" << endl;
    }
}