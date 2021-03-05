#pragma once

#include "math.h"

class Vect {
public:
    Vect();
    Vect(double, double, double);
    Vect(double, double, double, double);

    double magnitude() const;

    Vect normalize() const;
    Vect negative() const;

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
