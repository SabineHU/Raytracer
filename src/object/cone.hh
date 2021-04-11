#pragma once

#include "object.hh"

class Cone : public Object {
public:
    Cone();
    Cone(const Point3&, double, double);

    /* Methods */
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

private:
    Vect get_normal(const Point3& point) const;

    /* Attributes */
    Point3 position;
    double radius;
    double height;
};
