#pragma once

#include "object.hh"
#include "vector3.hh"

class Sphere : public Object {
public:

    Sphere();
    Sphere(const Vect&, double);
    Sphere(const Vect&, double, shared_texture);

    Vect getSphereCenter () { return center; }
    double getSphereRadius () { return radius; }

    virtual Vect get_normal_at(const Vect& point) const override;
    virtual double find_intersection(const Ray& ray) const override;

    /* Attribute */
    Vect center;
    double radius;

};
