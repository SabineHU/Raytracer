#pragma once

#include "vector3.hh"

class Ray {
public:
    Ray();
    Ray(const Vect&, const Vect&);

    Ray get_reflection_ray(const Vect& normal) const;
    Point3 at(double i) const;

    Vect get_reflection_dir(const Vect& normal) const;
    Vect get_refraction_dir(const Vect& normal, double ior=1.33) const;
    // ior water = 1.33
    // ior air = 1

    /* Attributes */
    Vect origin;
    Vect direction;
};
