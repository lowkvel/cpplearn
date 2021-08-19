#include <iostream>

using namespace std;

const double PI = 3.14;

class Circle {
    // access control
    public:

    // property
    int radius;

    // behavior
    double calculate_circumference() {
        return 2 * PI * radius;
    }
};

class Student {
    // access control
    public:

    // property
    int id;
    string name;

    // behavior
    void showStudent() {
        cout << id << " " << name << endl;
    }

    void setId(int n) {
        id = n;
    }

    void setName(string s) {
        name = s;
    }
};

class Person {

public:
    string name;

protected:
    string car;

private:
    string password;

public:
    void initiate() {
        name = "Alice";
        car = "bmw";
        password = "111";
    }

};

// p99-p105, object encapsulation
int main() {

    cout << "object encapsulation" << endl;

    /*
        object encapsulation

        class class_name() {
            // access control
            public:             // access allowed within class, access allowed outside class
            protected:          // access allowed within class and inherited class, access disallowed outside class 
            private:            // access allowed within class, access disallowed outside class and inherited class

            // property
            variable_type variable_name;
            ...

            // bahavior
            return_type func() {
                ...
            }
            ...
        }

    */

    // instantiate a Circle object c1 and calculate its circumference given radius
    Circle c1;
    c1.radius = 2;
    cout << c1.calculate_circumference() << endl;

    // instantiate a Studeng object s1 and show its id and name
    Student s1;
    s1.setId(1);
    s1.setName("Alice");
    s1.showStudent();

    // instantiate a Person object p1 and try some access control
    Person p1;
    p1.initiate();
    cout << p1.name << endl;
    //cout << p1.car << endl;         // protected, outside of class Person, inaccessible
    //cout << p1.password << endl;    // private, outside of class Person, inaccessible


    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

