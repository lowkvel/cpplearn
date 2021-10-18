# pragma once

# include <iostream>

using namespace std;

class User {
public:
    int id;
    string name;
    string password;

public:
    virtual void operationMenu() = 0;   // pure virtual function makes UserGroup an abstract class, non-instantiable
};
