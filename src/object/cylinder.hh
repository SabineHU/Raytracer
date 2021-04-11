#pragma once

#include "object.hh"

class Cylinder : public Object {
public:
    Cylinder();
    Cylinder(const Point3&, const Point3&, double);

    /* Methods */
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const override;

private:
    /* Attributes */
    Point3 bottom;
    Point3 top;
    double radius;

    Vect normal;
};
