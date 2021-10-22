# pragma once

# include <iostream>
# include <fstream>
# include <vector>

# include "globalConstants.h"
# include "computerRoom.h"
# include "user.h"

using namespace std;

class Student: public User {

public: 
    // member fields [int id, string name, string password] inherited from parent User
    vector<ComputerRoom> vc;


public:
    Student();
    
    Student(int id, string name, string password);
    
    virtual void operationMenu();   // overrode pure virtual function from parent class User makes Student instantiable
    
    void vcInit();

    void makeReservation();         // make a reservation
    
    void showMyReservations();      // show my reservations
    
    void showAllReservations();     // show all reservations

    void cancelReservation();       // cancel a reservation
};
