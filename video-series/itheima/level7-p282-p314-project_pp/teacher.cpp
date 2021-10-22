# include "teacher.h"

Teacher::Teacher() {
    this->id = 0;
    this->name = "";
    this->password = "";
}

Teacher::Teacher(int id, string name, string password) {
    this->id = id;
    this->name = name;
    this->password = password;
}

void Teacher::operationMenu() {
    cout << "-----------------------------------" << endl;
    cout << "Choose your options from below: " << endl;
    cout << "[1] Show all reservations" << endl;
    cout << "[2] Validate reservation" << endl;
    cout << "[0] Logout" << endl;
    cout << "-----------------------------------" << endl;
}

void Teacher::showAllReservations() {
    Reservation res;
    if (res.size == 0) {
        cout << "No records" << endl;
        return;
    }

    for (int i = 0; i < res.size; i++) {
        cout << i << " ";
        cout << "date:" << res.reservations[i]["date"] << " ";
        cout << "time:" << (res.reservations[i]["time"] == "1" ? "morning" : "afternoon") << " ";
        cout << "room:" << res.reservations[i]["room"] << " ";
        cout << "stu_id:" << res.reservations[i]["stuid"] << " ";
        cout << "stu_name:" << res.reservations[i]["stuname"] << " ";
        cout << "status: ";
        if (res.reservations[i]["status"] == "1") cout << "under review";
        else if (res.reservations[i]["status"] == "1") cout << "reserved";
        else if (res.reservations[i]["status"] == "-1") cout << "reservation failed";
        else cout << "reservation canceled";
        cout << endl;
    }
}

void Teacher::validateReservation() {

}
