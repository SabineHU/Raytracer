#pragma once

#include "object.hh"

class Cone : public Object {
public:
    Cone();
    Cone(const Point3&, double, double);

    /* Methods */
    virtual Vect get_normal_at(const Point3& point, double u, double v) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

private:
    /* Attributes */
    Point3 position;
    double radius;
    double height;
};
