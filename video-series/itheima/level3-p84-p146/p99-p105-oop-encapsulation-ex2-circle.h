#pragma once

#include <iostream>

#include "p99-p105-oop-encapsulation-ex2-point.h"

using namespace std;

class Circle {
private:
    Point center;
    double radius;

public:
    void setCenter(Point c);
    Point getCenter();
    void setRadius(double r);
    double getRadius();

    string checkLocation(Point p);
};