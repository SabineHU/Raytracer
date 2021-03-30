#pragma once

#include "object.hh"

class Capsule : public Object {
public:
    Capsule();
    Capsule(const Point3&, const Point3&, double);

    /* Methods */
    virtual Vect get_normal_at(const Vect& point) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

    virtual int get_isolevel_at(const Point3&) const override;

private:
    /* Attributes */
    Point3 bottom;
    Point3 top;
    double radius;
};
