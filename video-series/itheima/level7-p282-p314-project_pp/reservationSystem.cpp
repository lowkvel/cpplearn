# include <iostream>
# include <fstream>

# include "globalConstants.h"
# include "user.h"
# include "student.h"
# include "teacher.h"
# include "manager.h"

using namespace std;

void main_func();
void login(string filename, int userType);
void managerMenu(User * &m);
void teacherMenu(User * &t);
void studentMenu(User * &s);

/*
    build command:
    /usr/bin/clang++ -std=c++11 -g reservationSystem.cpp student.cpp teacher.cpp manager.cpp -o reservationSystem

    files:
    reservationSystem.cpp student.cpp teacher.cpp manager.cpp
*/

int main() {

    main_func();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void main_func() {
    int option = 0;
    while (true) {
        cout << "-----------------------------------" << endl;
        cout << "Choose your user group from below: " << endl;
        cout << "[1] Student" << endl;
        cout << "[2] Teacher" << endl;
        cout << "[3] Manager" << endl;
        cout << "[0] Quit" << endl;
        cout << "-----------------------------------" << endl;

        cout << "Your choice: ";
        cin >> option;

        switch (option) {
            case 1:
                login(STUDENT_FILE, 1);     // student
                break;
            case 2:
                login(TEACHER_FILE, 2);     // teacher
                break;  
            case 3:
                login(MANAGER_FILE, 3);     // manager
                break;
            case 0:             // quit system
                cout << "\nQuitted." << endl;
                return;
                break;
            default:            // wrong input
                cout << "\nWront input." << endl;
                break;
        }
    }
}

void login(string filename, int userType) {
    // authentication information gathering
    int id = 0;
    string name = "";
    string password = "";
    cout << "Please input your id: ";       cin >> id;
    cout << "Please input your name: ";     cin >> name;
    cout << "Please input your password: "; cin >> password;

    // open file, and check for file existence
    ifstream ifs;
    ifs.open(filename, ios::in);
    if (!ifs.is_open()) {
        cout << "File \"" << filename << "\" not exist." << endl;
        ifs.close();
        return;
    }

    // authentication, pair-wise comparision
    int f_id = 0; 
    string f_name = ""; 
    string f_password = "";
    bool auth = false;
    while (ifs >> f_id && ifs >> f_name && ifs >> f_password)
        if (id == f_id && name == f_name && password == f_password) {
            cout << "\nAuthentication successful" << endl;
            auth = true;
            break;
        }
    ifs.close();

    // specific user creation
    User *user = NULL;     // polymorphism
    if (auth)
        switch (userType) {
            case 1: user = new Student(id, name, password); studentMenu(user); return; break;
            case 2: user = new Teacher(id, name, password); teacherMenu(user); return; break;
            case 3: user = new Manager(id, name, password); managerMenu(user); return; break;
        }

    // authentication failed
    cout << "\nAuthentication failed" << endl;
}

void managerMenu(User * &m) {
    int option = 0;
    while (true) {
        m->operationMenu();                 // can only use user's member function only now
        Manager * manager = (Manager *)m;   // explicit transform, to use manager's other member functions

        cout << "Your choice: ";
        cin >> option;

        switch (option) {
            case 1:
                manager->addUser();
                break;
            case 2:
                manager->showAllUsers();
                break;
            case 3:
                manager->showComputerRooms();
                break;
            case 4:
                manager->clearReservation();
                break;
            case 0:
                delete manager;
                cout << "\nLogout successful" << endl;
                return;
                break;
            default:
                cout << "\nWront input." << endl;
                break;
        }
    }
}

void teacherMenu(User * &t) {

}

void studentMenu(User * &s) {

}
