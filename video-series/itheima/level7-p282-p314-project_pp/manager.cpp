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
    while (true) {
        bool selected = false;

        cout << "Please choose a user type \n[1. Student; 2. Teacher; 3. Manager]: ";
        int option = 0;
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

    int id = 0;             cout << "Please input desired id: ";        cin >> id;
    string name = "";       cout << "Please input desired name: ";      cin >> name;
    string password = "";   cout << "Please input desired password: ";  cin >> password;
    
    cout << "\nUser added" << endl;
    ofs << id << " " << name << " " << password << " " << endl;
    ofs.close();
}

void Manager::showAllUsers() {

}

void Manager::showComputerRooms() {

}

void Manager::clearReservation() {

}
