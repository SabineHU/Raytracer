#pragma once

#include "object.hh"

class Capsule : public Object {
public:
    Capsule();
    Capsule(const Point3&, const Point3&, double);

    /* Methods */
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

private:
    Vect get_normal(const Point3& point) const;

    /* Attributes */
    Point3 bottom;
    Point3 top;
    double radius;
};
