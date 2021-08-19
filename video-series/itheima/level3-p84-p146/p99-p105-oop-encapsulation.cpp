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

// p99-p105, object encapsulation
int main() {

    cout << "object encapsulation" << endl;

    /*
        object encapsulation

        class class_name() {
            // access control
            public:             // access allowed within class, access allowed outside class
            protected:          // access allowed within class, access disallowed outside class
            private:            // access allowed within class, access disallowed outside class

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


    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

