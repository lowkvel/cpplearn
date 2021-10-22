# pragma once

# include <iostream>
# include <fstream>
# include <map>

# include "globalConstants.h"

using namespace std;

class Reservation {
public:
    int size;
    map<int, map<string, string> > reservations;

public:
    Reservation();              // constructor

    void updateReservation();   // update reservation
};
