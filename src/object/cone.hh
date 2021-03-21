#pragma once

#include "object.hh"

class Cone : public Object {
public:

    Cone();
    Cone(const Point3&, double, double);
    Cone(const Point3&, double, double, shared_texture);
    Cone(const Point3&, double, double, const Color&);

    /* Methods */
    virtual Vect get_normal_at(const Vect& point) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max) override;

    virtual int get_isolevel_at(const Point3&) const override;

    /* Attributes */
    Point3 position;
    double radius;
    double height;
};
