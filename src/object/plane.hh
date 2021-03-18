#pragma once

#include "object.hh"
#include "vector3.hh"

class Plane : public Object {
public:
    Plane();
    Plane(const Vect&, double);
    Plane(const Vect&, double, shared_texture);
    Plane(const Vect&, double, const Color&);

    /* Methods */
    virtual Vect get_normal_at(const Vect&, const Point3&) const override;
    virtual double find_intersection(const Ray& ray) override;

    virtual int get_isolevel_at(const Point3&) const override;

    /* Attributes */
    Vect normal;
    double distance;
};
