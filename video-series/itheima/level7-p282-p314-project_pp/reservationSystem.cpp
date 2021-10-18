# include <iostream>

using namespace std;

int main_func();

// build command:
// /usr/bin/clang++ -std=c++11 -g reservationSystem.cpp -o reservationSystem
/*
reservationSystem.cpp 
*/

int main() {

    main_func();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

int main_func() {
    int select = 0;
    while (true) {
        cout << "-----------------------------------" << endl;
        cout << "Choose your user group from below: " << endl;
        cout << "[1] Student" << endl;
        cout << "[2] Teacher" << endl;
        cout << "[3] Manager" << endl;
        cout << "[0] Quit" << endl;
        cout << "-----------------------------------" << endl;

        cout << "Your choice: " << endl;
        cin >> select;

        switch (select) {
            case 1:             // student
                break;
            case 2:             // teacher
                break;  
            case 3:             // manager
                break;
            case 0:             // quit system
                cout << "Quitted." << endl;
                return 0;
                break;
            default:            // wrong input
                cout << "Wront input." << endl;
                break;
        }
    }
}
