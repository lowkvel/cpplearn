#include <iostream>
#include <math.h>

using namespace std;

class Circle {
private:
    double centerx;
    double centery;
    double radius;

public:
    void setCenterx(double x) {
        centerx = x;
    }
    double getCenterx() {
        return centerx;
    }
    void setCentery(double y) {
        centery = y;
    }
    double getCentery() {
        return centery;
    }
    void setRadius(double r) {
        radius = r;
    }
    double getRadius() {
        return radius;
    }

    string checkLocation(double x, double y) {
        double distancep = 0;
        distancep = pow((centerx - x), 2) + pow((centery - y), 2);
        
        if (distancep == pow(radius, 2))
            return "on circle";
        else if (distancep > radius)
            return "outside circle";
        else
            return "inside circle";
    }
};

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

    cout << c.checkLocation(1, 1) << endl;

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

