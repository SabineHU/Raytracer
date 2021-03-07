#pragma once

#include "vector3.hh"

class Ray {
public:
    Ray();
    Ray(const Vect&, const Vect&);

    Ray get_reflection_ray(const Vect& normal) const;
    Point3 at(double i) const;

    /* Attributes */
    Vect origin;
    Vect direction;
};

