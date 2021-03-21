#pragma once

#include "object.hh"

class Cylinder : public Object {
public:
    Cylinder();
    Cylinder(const Point3&, double, double);
    Cylinder(const Point3&, double, double, shared_texture);
    Cylinder(const Point3&, double, double, const Color&);

    /* Methods */
    virtual Vect get_normal_at(const Vect& point) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max) override;

    virtual int get_isolevel_at(const Point3&) const override;

    /* Attributes */
    Point3 center;
    double radius;
    double height;
};
