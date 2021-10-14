# include <iostream>

# include "speechManager.h"

using namespace std;

void main_func();

// build command:
// /usr/bin/clang++ -std=c++11 -g speechContestManagementSystem.cpp speechManager.cpp -o speechContestManagementSystem
/*
speechContestManagementSystem.cpp speechManager.cpp
*/

int main() {

    SpeechManager sm;
    int choice = 0;

    while (true) {
        sm.showMenu();

        cout << "please type in your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:                 // begin
                break;
            case 2:                 // previous
                break;
            case 3:                 // clear
                break;
            case 0:                 // quit
                sm.quitSystem();
                break;
            default:
                system("clear");
                break;
        }
    }

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}
