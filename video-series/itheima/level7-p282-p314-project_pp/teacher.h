# pragma once

# include <iostream>

# include "user.h"

using namespace std;

class Teacher: public User {
/*
public: 
    // member fields [int id, string name, string password] inherited from parent User
*/

public:
    Teacher();

    Teacher(int id, string name, string password);

    virtual void operationMenu();   // overrode pure virtual function from parent class User makes Student instantiable

    void showAllReservations();     // show all reservations

    void validateReservation();     // validate a selected reservation
};
