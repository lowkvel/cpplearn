#pragma once

#include <iostream>

using namespace std;

class Point {
private:
    double x;
    double y;

public:
    void setx(double x);
    double getx();
    void sety(double y);
    double gety();
};