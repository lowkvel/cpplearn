#include <iostream>
#include <math.h>

#include "p99-p105-oop-encapsulation-ex2-circle.h"
#include "p99-p105-oop-encapsulation-ex2-point.h"

using namespace std;

// build command:
// /usr/bin/clang++ -std=c++11 -g p99-p105-oop-encapsulation-ex2.cpp p99-p105-oop-encapsulation-ex2-circle.cpp p99-p105-oop-encapsulation-ex2-point.cpp -o p99-p105-oop-encapsulation-ex2

// p99-p105, object encapsulation ex2
int main() {

    cout << "object encapsulation ex2" << endl;

    /*
        object encapsulation ex2
    */

    Circle c;
    c.setCenterx(0);
    c.setCentery(0);
    c.setRadius(1);

    cout << c.checkLocation(0.1, 1) << endl;

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

