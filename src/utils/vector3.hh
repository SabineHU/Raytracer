#pragma once

#include "math.h"

class Vect {
public:
    Vect();
    Vect(double, double, double);

    double magnitude() const;

    Vect normalize() const;
    Vect negative() const;

    double dot_x() const;
    double dot_y() const;
    double dot_z() const;

    Vect operator+(const Vect& u) const;
    Vect operator-(const Vect& u) const;
    Vect operator*(const Vect& u) const;
    Vect operator/(const Vect& u) const;

    Vect& operator+=(const Vect& u);
    Vect& operator-=(const Vect& u);
    Vect& operator*=(const Vect& u);
    Vect& operator/=(const Vect& u);

    Vect operator+(double u) const;
    Vect operator-(double u) const;
    Vect operator*(double u) const;
    Vect operator/(double u) const;

    Vect& operator+=(double u);
    Vect& operator-=(double u);
    Vect& operator*=(double u);
    Vect& operator/=(double u);

    Vect clamp() const;

    /* Attributes */
    double x, y, z, s;

};

using Point3 = Vect;
using Color = Vect;
