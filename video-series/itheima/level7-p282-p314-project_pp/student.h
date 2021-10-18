# pragma once

# include <iostream>

# include "user.h"

using namespace std;

class Student: public User {
/*
public: 
    // member fields [int id, string name, string password] inherited from parent User
*/

public:
    Student();
    
    Student(int id, string name, string password);
    
    virtual void operationMenu();   // overrode pure virtual function from parent class User makes Student instantiable
    
    void makeReservation();         // make a reservation
    
    void showMyReservations();      // show my reservations
    
    void showAllReservations();     // show all reservations

    void cancelReservation();       // cancel a reservation
};
