#pragma once

#include "math.h"

class Vect2 {
public:
    Vect2() : x(0), y(0) {}
    Vect2(double u, double v) : x(u), y(v) {}

    double x, y;
};

class Vect {
public:
    Vect();
    Vect(double, double, double);
    Vect(double, double, double, double);

    double square_length() const;
    double magnitude() const;

    Vect normalize() const;
    Vect negative() const;

    double dot_x() const;
    double dot_y() const;
    double dot_z() const;

    double sum() const;
    bool is_zero() const;

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

    bool operator==(const Vect& u) const;
    bool operator!=(const Vect& u) const;

    Vect clamp() const;

    /* Attributes */
    double x, y, z;
    double iso;

};

using Point3 = Vect;
using Color = Vect;
