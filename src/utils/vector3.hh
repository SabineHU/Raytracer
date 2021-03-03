#pragma once

#include "math.h"

class Vect {
    public:
    double x, y, z, s;

    Vect () : x(0), y(0), z(0), s(0) {}

    Vect (double a, double b, double c)
        : x(a), y(b), z(c), s(0)
    {}

    Vect (double a, double b, double c, double d)
        : x(a), y(b), z(c), s(d)
    {}

    // method functions
    double getVectX() { return x; }
    double getVectY() { return y; }
    double getVectZ() { return z; }

    double magnitude () {
        return sqrt((x*x) + (y*y) + (z*z));
    }

    Vect normalize () {
        double magnitude = sqrt((x*x) + (y*y) + (z*z));
        return Vect (x/magnitude, y/magnitude, z/magnitude);
    }

    Vect negative () {
        return Vect (-x, -y, -z);
    }

    double dotProduct(Vect v) {
        return x*v.getVectX() + y*v.getVectY() + z*v.getVectZ();
    }

    Vect crossProduct(Vect v) {
        return Vect (y*v.getVectZ() - z*v.getVectY(), z*v.getVectX() - x*v.getVectZ(), x*v.getVectY() - y*v.getVectX());
    }

    Vect operator+(const Vect& u) const {
        return Vect(x + u.x, y + u.y, z + u.z, s);
    }
    Vect operator-(const Vect& u) const {
        return Vect(x - u.x, y - u.y, z - u.z, s);
    }
    Vect operator*(const Vect& u) const {
        return Vect(x * u.x, y * u.y, z * u.z, s);
    }
    Vect operator/(const Vect& u) const {
        return Vect(x / u.x, y / u.y, z / u.z, s);
    }

    Vect operator+(double u) const {
    return Vect(x + u, y + u, z + u, s);
    }
    Vect operator-(double u) const {
    return Vect(x - u, y - u, z - u, s);
    }
    Vect operator*(double u) const {
    return Vect(x * u, y * u, z * u, s);
    }
    Vect operator/(double u) const {
    return Vect(x / u, y / u, z / u, s);
    }

    Vect clip() {
        double alllight = x + y + z;
        double excesslight = alllight - 3;
        if (excesslight > 0) {
            x = x + excesslight*(x/alllight);
            y = y + excesslight*(y/alllight);
            z = z + excesslight*(z/alllight);
        }
        if (x > 1) {x = 1;}
        if (y > 1) {y = 1;}
        if (z > 1) {z = 1;}
        if (x < 0) {x = 0;}
        if (y < 0) {y = 0;}
        if (z < 0) {z = 0;}

        return Vect(x, y, z, s);
    }
};

using Point3 = Vect;
using Color = Vect;
