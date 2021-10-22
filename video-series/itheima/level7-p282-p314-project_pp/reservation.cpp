# include "reservation.h"

Reservation::Reservation() {
    ifstream ifs;
    ifs.open(RESERVATION_FILE, ios::in);

    string date;    string time;    string room;
    string stuid;   string stuname; string status;
    this->size = 0;

    while (ifs >> date && ifs >> time && ifs >> stuid && ifs >> stuname && ifs >> room && ifs >> status) {
        int pos = 0;
        map<string, string> m;

        pos = date.find(":");
        if (pos != -1) m.insert(make_pair(date.substr(0, pos), date.substr(pos + 1, date.size() - pos)));
        pos = time.find(":");
        if (pos != -1) m.insert(make_pair(time.substr(0, pos), time.substr(pos + 1, time.size() - pos)));
        pos = stuid.find(":");
        if (pos != -1) m.insert(make_pair(stuid.substr(0, pos), stuid.substr(pos + 1, stuid.size() - pos)));
        pos = stuname.find(":");
        if (pos != -1) m.insert(make_pair(stuname.substr(0, pos), stuname.substr(pos + 1, stuname.size() - pos)));
        pos = room.find(":");
        if (pos != -1) m.insert(make_pair(room.substr(0, pos), room.substr(pos + 1, room.size() - pos)));
        pos = status.find(":");
        if (pos != -1) m.insert(make_pair(status.substr(0, pos), status.substr(pos + 1, status.size() - pos)));
        
        this->reservations.insert(make_pair(this->size, m));
        this->size++;
    }

    ifs.close();

    // tester
    // for (map<int, map<string, string> >::iterator it = reservations.begin(); it != reservations.end(); it++) {
    //     cout << "[" << it->first << "] ";
    //     for (map<string, string>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
    //         cout << it2->first << ": " << it2->second << " ";
    //     cout << endl;
    // }
}

void Reservation::updateReservation() {
    if (this->size == 0) return;

    ofstream ofs(RESERVATION_FILE, ios::out | ios::trunc);

    for (int i = 0; i < this->size; i++) {
        ofs << "date:" << this->reservations[i]["date"] << " ";
        ofs << "time:" << this->reservations[i]["time"] << " ";
        ofs << "stuid:" << this->reservations[i]["stuid"] << " ";
        ofs << "stuname:" << this->reservations[i]["stuname"] << " ";
        ofs << "room:" << this->reservations[i]["room"] << " ";
        ofs << "status:" << this->reservations[i]["status"] << endl;
    }

    ofs.close();
}
