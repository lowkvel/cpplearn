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

// p99-p105, object encapsulation
int main() {

    cout << "object encapsulation" << endl;

    /*
        object encapsulation


    */

    // instantiate a Circle object c1 and calculate its circumference given radius
    Circle c1;
    c1.radius = 2;
    cout << c1.calculate_circumference() << endl;



    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

