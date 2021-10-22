# pragma once

# include <iostream>
# include <fstream>
# include <vector>

# include "globalConstants.h"
# include "computerRoom.h"
# include "user.h"
# include "student.h"
# include "teacher.h"

using namespace std;

class Manager: public User {
public: 
    // member fields [int id, string name, string password] inherited from parent User
    vector<Student> vs;
    vector<Teacher> vt;
    vector<Manager> vm;
    vector<ComputerRoom> vc;

public:
    Manager();

    Manager(int id, string name, string password);

    virtual void operationMenu();   // overrode pure virtual function from parent class User makes Student instantiable

    void addUser();                 // add a user

    void showAllUsers();            // show all users

    void showComputerRooms();       // show all computer rooms

    void clearReservation();        // clear all reservations

    void vstmInit();
    void vcInit();

    bool checkDuplicates(int id, int userType);
};
