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

    this->vcInit();
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

// init vc vector
void Student::vcInit() {
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);

    ComputerRoom cr;
    while (ifs >> cr.id && ifs >> cr.maxNum) vc.push_back(cr);
    ifs.close();
}

void Student::makeReservation() {
    cout << "Please choose a date" << endl;
    cout << "1. Mon; 2. Tue; 3. Wed; 4. Thu; 5. Fri: ";
    int date = 0;
    while (true) {
        cin >> date;
        if (date >= 1 && date <= 5) break;
        cout << "\nWrong input." << endl;
    }

    cout << "Please choose a time" << endl;
    cout << "1. Morning; 2. Afternoon: ";
    int time = 0;
    while (true) {
        cin >> time;
        if (time >= 1 && time <= 2) break;
        cout << "\nWrong input." << endl;
    }

    int room = 0;
    cout << "Please choose a time" << endl;
    cout << "1. 20; 2. 50; 3. 100: ";
    while (true) {
        cin >> room;
        if (room >= 1 && room <= 3) break;
        cout << "\nWrong input." << endl;
    }

    cout << "Reservation made, waiting for validation" << endl;

    ofstream ofs(RESERVATION_FILE, ios::app);
    ofs << "date:" << date << " ";
    ofs << "time:" << time << " ";
    ofs << "stuid:" << this->id << " ";
    ofs << "stuname:" << this->name << " ";
    ofs << "roomid:" << room << " ";
    ofs << "status:" << 1 << endl;      // status 1, under review
    ofs.close();
}

void Student::showMyReservations() {

}

void Student::showAllReservations() {

}

void Student::cancelReservation() {

}
