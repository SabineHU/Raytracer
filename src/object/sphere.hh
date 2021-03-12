#pragma once

#include "object.hh"

class Sphere : public Object {
public:

    Sphere();
    Sphere(const Vect&, double);
    Sphere(const Vect&, double, shared_texture);
    Sphere(const Vect&, double, const Color&);

    /* Methods */
    virtual Vect get_normal_at(const Vect& point) const override;
    virtual double find_intersection(const Ray& ray) const override;

    virtual int get_isolevel_at(const Point3&) const override;

    /* Attribute */
    Vect center;
    double radius;

};
