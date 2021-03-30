#pragma once

#include "object.hh"

class Cone : public Object {
public:
    Cone();
    Cone(const Point3&, double, double);

    /* Methods */
    virtual Vect get_normal_at(const Vect& point) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

    virtual int get_isolevel_at(const Point3&) const override;

private:
    /* Attributes */
    Point3 position;
    double radius;
    double height;
};
