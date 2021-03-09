#pragma once

#include "object.hh"

class Cone : public Object {
public:

    Cone();
    Cone(const Point3&, double, double);
    Cone(const Point3&, double, double, shared_texture);

    virtual Vect get_normal_at(const Vect& point) const override;
    virtual double find_intersection(const Ray& ray) const override;

    Point3 position;
    double radius;
    double height;
};
