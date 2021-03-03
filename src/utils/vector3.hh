#pragma once

#include "math.h"

class Vect {
public:
    Vect();
    Vect(double, double, double);
    Vect(double, double, double, double);

    double getVectX() { return x; }
    double getVectY() { return y; }
    double getVectZ() { return z; }

    double magnitude();

    Vect normalize();
    Vect negative();

    double dotProduct(Vect v) {
        return x*v.getVectX() + y*v.getVectY() + z*v.getVectZ();
    }

    Vect crossProduct(Vect v) {
        return Vect (y*v.getVectZ() - z*v.getVectY(), z*v.getVectX() - x*v.getVectZ(), x*v.getVectY() - y*v.getVectX());
    }

    Vect operator+(const Vect& u) const;
    Vect operator-(const Vect& u) const;
    Vect operator*(const Vect& u) const;
    Vect operator/(const Vect& u) const;

    Vect operator+(double u) const;
    Vect operator-(double u) const;
    Vect operator*(double u) const;
    Vect operator/(double u) const;

    Vect clamp() const;

    /* Attributes */
    double x, y, z, s;

};

using Point3 = Vect;
using Color = Vect;
