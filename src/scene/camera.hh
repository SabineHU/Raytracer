#pragma once

#include "vector3.hh"
#include "ray.hh"

class Camera {
public:

    Camera();
    Camera(const Vect&, const Vect&, const Vect&);

    Vect get_position() const { return campos; }
    Ray get_ray(double x, double y) const;

private:
    Vect get_ray_direction(double x, double y) const;

private:
    /* Attributes */
    Vect campos;
    Vect camdir;
    Vect camright;
    Vect camdown;

};
