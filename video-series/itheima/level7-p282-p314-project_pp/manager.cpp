# include "manager.h"

Manager::Manager() {
    this->id = 0;
    this->name = "";
    this->password = "";
}

Manager::Manager(int id, string name, string password) {
    this->id = id;
    this->name = name;
    this->password = password;

    this->vstmInit();
}

void Manager::operationMenu() {
    cout << "-----------------------------------" << endl;
    cout << "Choose your options from below: " << endl;
    cout << "[1] Add a user" << endl;
    cout << "[2] Show all users" << endl;
    cout << "[3] Show all computer rooms" << endl;
    cout << "[4] Clear reservations" << endl;
    cout << "[0] Logout" << endl;
    cout << "-----------------------------------" << endl;
}

void Manager::addUser() {
    string filename;
    int option = 0;
    while (true) {      // make a selection
        bool selected = false;

        cout << "Please choose a user type \n[1. Student; 2. Teacher; 3. Manager]: ";
        cin >> option;

        switch (option) {
            case 1: filename = STUDENT_FILE; selected = true; break;
            case 2: filename = TEACHER_FILE; selected = true; break;
            case 3: filename = MANAGER_FILE; selected = true; break;
            default: cout << "\nWrong input." << endl; break;
        }

        if (selected) break;
    }

    ofstream ofs;
    ofs.open(filename, ios::out | ios::app);

    int id = 0;             cout << "Please input desired id: ";
    while (true) {      // check for duplicates
        cin >> id;
        if (this->checkDuplicates(id, option))
            cout << "Duplicated user id detected, please input a new one: ";
        else
            break;
    }
    string name = "";       cout << "Please input desired name: ";      cin >> name;
    string password = "";   cout << "Please input desired password: ";  cin >> password;
    
    cout << "\nUser added" << endl;
    this->vstmInit();   // re-initialize vstm vector to prevent newly added user id got repeated
    ofs << id << " " << name << " " << password << " " << endl;
    ofs.close();
}

void Manager::showAllUsers() {

}

void Manager::showComputerRooms() {

}

void Manager::clearReservation() {

}

// init vstm vector for duplicates detection
void Manager::vstmInit() {
    ifstream ifs;
    vs.clear(); Student s;
    vt.clear(); Teacher t;
    vm.clear(); Manager m;
    
    ifs.open(STUDENT_FILE, ios::in);
    if (!ifs.is_open()) { cout << "File not exist." << endl; return; }
    while (ifs >> s.id && ifs >> s.name && ifs >> s.password) vs.push_back(s);
    ifs.close();

    ifs.open(TEACHER_FILE, ios::in);
    if (!ifs.is_open()) { cout << "File not exist." << endl; return; }
    while (ifs >> t.id && ifs >> t.name && ifs >> t.password) vt.push_back(t);
    ifs.close();

    ifs.open(MANAGER_FILE, ios::in);
    if (!ifs.is_open()) { cout << "File not exist." << endl; return; }
    while (ifs >> m.id && ifs >> m.name && ifs >> m.password) vm.push_back(m);
    ifs.close();
}

// check for duplication 
bool Manager::checkDuplicates(int id, int userType) {
    switch (userType) {
        case 1:
            for (vector<Student>::iterator it = vs.begin(); it != vs.end(); it++)
                if (id == it->id) return true;
            break;
        case 2:
            for (vector<Teacher>::iterator it = vt.begin(); it != vt.end(); it++)
                if (id == it->id) return true;
            break;
        case 3:
            for (vector<Manager>::iterator it = vm.begin(); it != vm.end(); it++)
                if (id == it->id) return true;
            break;
        default:
            return false;
            break;
    }
    return false;
}
