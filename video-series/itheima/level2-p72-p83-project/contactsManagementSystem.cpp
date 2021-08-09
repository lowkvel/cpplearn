#include <iostream>

using namespace std;

void showMenu();

int main() {

    showMenu();

    // options selected by user, initiated to 0
    int option = 0;

    // main loop
    while (true) {

        // get the option
        cin >> option;

        switch (option) {
            case 1:     // add
                break;
            case 2:     // show
                showMenu();
                break;
            case 3:     // delete
                break;
            case 4:     // find
                break;
            case 5:     // modify
                break;
            case 6:     // clear
                break;
            case 0:     // quit
                cout << "quitted" << endl;
                return 0;
                break;
            default:    // default
                break;
        }


    }

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void showMenu() {
    cout << "1. add a contact" << endl;
    cout << "2. show all contacts" << endl;
    cout << "3. delete a contact" << endl;
    cout << "4. find a contact" << endl;
    cout << "5. modify a contact" << endl;
    cout << "6. clear all contacts" << endl;
    cout << "0. quit" << endl;
}