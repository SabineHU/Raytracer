#pragma once

#include "object.hh"

class CappedCone : public Object {
public:

    CappedCone();
    CappedCone(const Point3&, const Point3&, double, double);

    /* Methods */
    virtual Vect get_normal_at(const Point3& point, double u, double v) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

private:
    /* Attributes */
    Point3 bottom;
    Point3 top;
    double radius_bottom;
    double radius_top;

    Vect normal;
};
