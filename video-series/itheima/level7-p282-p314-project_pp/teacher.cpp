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
        else if (res.reservations[i]["status"] == "2") cout << "reserved";
        else if (res.reservations[i]["status"] == "-1") cout << "reservation failed";
        else cout << "reservation canceled";
        cout << endl;
    }
}

void Teacher::validateReservation() {
    Reservation res;
    if (res.size == 0) {
        cout << "No records" << endl;
        return;
    }

    cout << "You may only validate reservation which is under review" << endl;
    vector<int> v;
    int index = 1;
    for (int i = 0; i < res.size; i++) {
        if (res.reservations[i]["status"] == "1") {
            v.push_back(i);
            cout << i << " ";
            cout << "date:" << res.reservations[i]["date"] << " ";
            cout << "time:" << (res.reservations[i]["time"] == "1" ? "morning" : "afternoon") << " ";
            cout << "room:" << res.reservations[i]["room"] << " ";
            cout << "stu_id:" << res.reservations[i]["stuid"] << " ";
            cout << "stu_name:" << res.reservations[i]["stuname"] << " ";
            cout << "status: ";
            if (res.reservations[i]["status"] == "1") cout << "under review";
            else if (res.reservations[i]["status"] == "2") cout << "reserved";
            else if (res.reservations[i]["status"] == "-1") cout << "reservation failed";
            else cout << "reservation canceled";
            cout << endl;
        }
    }

    cout << "Please choose a reservation to approve [-1. return]: ";
    int option = 0;
    while (true) {
        cin >> option;
        if (option == -1) break;

        bool existence = false;
        if (option > 0) 
            for (int i = 0; i < v.size(); i++) 
                if (v[i] == option) {
                    existence = true;
                    break;
                }
        
        if (existence) {
            res.reservations[option]["status"] = "2";
            res.updateReservation();
            cout << "Reservation approved" << endl;
            break;
        } else
            cout << "Wrong input, please re-choose: ";
    }
}
