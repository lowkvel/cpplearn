#include <math.h>

#include "p99-p105-oop-encapsulation-ex2-circle.h"

void Circle::setCenter(Point p) {
    center =p;
}
Point Circle::getCenter() {
    return center;
}
void Circle::setRadius(double r) {
    radius = r;
}
double Circle::getRadius() {
    return radius;
}

string Circle::checkLocation(Point p) {
    double distancep = 0;
    distancep = pow((center.getx() - p.getx()), 2) + pow((center.gety() - p.gety()), 2);
        
    if (distancep == pow(radius, 2))
        return "on circle";
    else if (distancep > radius)
        return "outside circle";
    else
        return "inside circle";
}
