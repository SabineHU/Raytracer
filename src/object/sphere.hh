#pragma once

#include "object.hh"

class Sphere : public Object {
public:

    Sphere();
    Sphere(const Vect&, double);

    /* Methods */
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

    virtual int get_isolevel_at(const Point3&) const override;

private:
    Vect get_normal(const Point3& point) const;

    /* Attributes */
    Vect center;
    double radius;

};
