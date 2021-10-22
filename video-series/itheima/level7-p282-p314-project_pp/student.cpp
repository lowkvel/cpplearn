# include "student.h"

Student::Student() {
    this->id = 0;
    this->name = "";
    this->password = "";
}

Student::Student(int id, string name, string password) {
    this->id = id;
    this->name = name;
    this->password = password;
}

void Student::operationMenu() {
    cout << "-----------------------------------" << endl;
    cout << "Choose your options from below: " << endl;
    cout << "[1] Make reservation" << endl;
    cout << "[2] Show my reservations" << endl;
    cout << "[3] Show all reservations" << endl;
    cout << "[4] Cancel reservation" << endl;
    cout << "[0] Logout" << endl;
    cout << "-----------------------------------" << endl;
}

void Student::makeReservation() {

}

void Student::showMyReservations() {

}

void Student::showAllReservations() {

}

void Student::cancelReservation() {

}
