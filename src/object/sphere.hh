#pragma once

#include "object.hh"
#include "vector3.hh"

class Sphere : public Object {
public:

    Sphere();
    Sphere(Vect, double, Color);

    Vect getSphereCenter () { return center; }
    double getSphereRadius () { return radius; }

    virtual Color get_color() const override;
    virtual Vect get_normal_at(const Vect& point) const override;
    virtual double find_intersection(const Ray& ray) const override;

    /* Attribute */
    Vect center;
    double radius;
    Color color;

};
