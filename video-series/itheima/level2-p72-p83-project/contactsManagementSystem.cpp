#include <iostream>

using namespace std;

#define MAX_CONTACT_LIMIT 1000

void showMenu();
void addContact(struct contactBook* pcb);
void displayContact(const struct contactBook* pcb);
void deleteContact(struct contactBook* pcb);
int isExist(const struct contactBook* pcb, string s);
void findContact(const struct contactBook* pcb);

struct contact {
    string name;
    int sex;
    int age;
    string phone;
    string address;
};

struct contactBook {
    struct contact contactArr[MAX_CONTACT_LIMIT];
    int size;
};

int main() {

    struct contactBook cb;
    cb.size = 0;

    // options selected by user, initiated to 0
    int option = 0;

    // main loop
    while (true) {
        
        // show menu
        showMenu();

        // get the option
        cout << "input an option: ";
        cin >> option;

        switch (option) {
            case 1:     // add
                addContact(&cb);
                break;
            case 2:     // display
                displayContact(&cb);
                break;
            case 3:     // delete
                deleteContact(&cb);
                break;
            case 4:     // find
                findContact(&cb);
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
    cout << endl;
    cout << "1. add a contact" << endl;
    cout << "2. display all contacts" << endl;
    cout << "3. delete a contact" << endl;
    cout << "4. find a contact" << endl;
    cout << "5. modify a contact" << endl;
    cout << "6. clear all contacts" << endl;
    cout << "0. quit" << endl;
}

void addContact(struct contactBook* pcb) {

    // check for max contact limit
    if (pcb->size >= MAX_CONTACT_LIMIT) {
        cout << "max contact limit reached" << endl;
        return;
    } else {
        // name
        string name = "";
        cout << "input name: ";
        cin >> name;
        pcb->contactArr[pcb->size].name = name;

        // sex
        int sex = 0;
        while (true) {
            cout << "input sex [1-male, 2-female]: ";
            cin >> sex;

            if (sex == 1 || sex == 2) {
                pcb->contactArr[pcb->size].sex = sex;
                break;
            } else
                cout << "invalid sex" << endl;
        }

        // age
        int age = 0;
        while (true) {
            cout << "input age: ";
            cin >> age;

            if (age >= 0 && age <= 150) {
                pcb->contactArr[pcb->size].age = age;
                break;
            } else
                cout << "invalid age" << endl;
        }

        // phone
        string phone = "";
        cout << "input phone: ";
        cin >> phone;
        pcb->contactArr[pcb->size].phone = phone;

        // address
        string address = "";
        cout << "input address: ";
        cin >> address;
        pcb->contactArr[pcb->size].address = address;

        // comments
        system("clear");
        cout << "new contact added!" << endl;

        // increment the array size by 1
        pcb->size ++;
    }
}

void displayContact(const struct contactBook* pcb) {

    if (pcb->size <= 0) {
        cout << "no contact yet" << endl;
        return;
    }

    for (int i = 0; i < pcb->size; i++) {
        cout << "name: " << pcb->contactArr[i].name
            << "\tsex: " << (pcb->contactArr[i].sex == 1 ? "male" : "female")
            << "\tage: " << pcb->contactArr[i].age
            << "\tphone: " << pcb->contactArr[i].phone
            << "\taddress: " << pcb->contactArr[i].address << endl;
    }

    // comments
    cout << "all contact shown!" << endl;
}

int isExist(const struct contactBook* pcb, string s) {
    for (int i = 0; i < pcb->size; i++)
        if (pcb->contactArr[i].name == s)
            return i;
    return -1;
}

void deleteContact(struct contactBook* pcb) {

    // empty contact book
    if (pcb->size <= 0) {
        cout << "nothing to delete" << endl;
        return;
    } else {
        string name = "";
        cout << "input name to delete: ";
        cin >> name;

        // find location of the name
        int location = 0;
        location = isExist(pcb, name);
        if (location == -1) {
            cout << "deletion failed, contact not found" << endl;
            return;
        } else {
            for (int i = location; i < pcb->size; i++)
                pcb->contactArr[i] = pcb->contactArr[i+1];
            pcb->size --;
            cout << "deletion successful" << endl;
        }
    }
}

void findContact(const struct contactBook* pcb) {
    string name = "";
    cout << "input name to find: ";
    cin >> name;

    int location = 0;
    location = isExist(pcb, name);
    if (location == -1) {
        cout << "contact not found";
        return;
    } else {
        cout << "name: " << pcb->contactArr[location].name
            << "\tsex: " << (pcb->contactArr[location].sex == 1 ? "male" : "female")
            << "\tage: " << pcb->contactArr[location].age
            << "\tphone: " << pcb->contactArr[location].phone
            << "\taddress: " << pcb->contactArr[location].address << endl;
        cout << "contact found" << endl;
    }
}