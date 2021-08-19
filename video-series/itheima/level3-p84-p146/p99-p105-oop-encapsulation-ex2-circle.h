#pragma once

#include <iostream>

#include "p99-p105-oop-encapsulation-ex2-point.h"

using namespace std;

class Circle {
private:
    double centerx;
    double centery;
    double radius;

public:
    void setCenterx(double x);
    double getCenterx();
    void setCentery(double y);
    double getCentery();
    void setRadius(double r);
    double getRadius();

    string checkLocation(double x, double y);
};