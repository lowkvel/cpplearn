# pragma once

# include <iostream>

# include "user.h"

using namespace std;

class Manager {
/*
public: 
    // member fields [int id, string name, string password] inherited from parent User
*/

public:
    Manager();

    Manager(int id, string name, string password);

    virtual void operationMenu();   // overrode pure virtual function from parent class User makes Student instantiable

    void addUser();                 // add a user

    void showAllUsers();            // show all users

    void showComputerRooms();       // show all computer rooms

    void clearReservation();        // clear all reservations
};
