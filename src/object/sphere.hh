#pragma once

#include "object.hh"

class Sphere : public Object {
public:

    Sphere();
    Sphere(const Vect&, double);

    /* Methods */
    virtual Vect get_normal_at(const Point3& point, double u, double v) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

    virtual int get_isolevel_at(const Point3&) const override;

private:
    /* Attributes */
    Vect center;
    double radius;

};
