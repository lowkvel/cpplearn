#include <math.h>

#include "p99-p105-oop-encapsulation-ex2-circle.h"

void Circle::setCenterx(double x) {
    centerx = x;
}
double Circle::getCenterx() {
    return centerx;
}
void Circle::setCentery(double y) {
    centery = y;
}
double Circle::getCentery() {
    return centery;
}
void Circle::setRadius(double r) {
    radius = r;
}
double Circle::getRadius() {
    return radius;
}

string Circle::checkLocation(double x, double y) {
    double distancep = 0;
    distancep = pow((centerx - x), 2) + pow((centery - y), 2);
        
    if (distancep == pow(radius, 2))
        return "on circle";
    else if (distancep > radius)
        return "outside circle";
    else
        return "inside circle";
}
