#pragma once

#include "object.hh"

class Torus : public Object {
public:

    Torus();
    Torus(const Point3&);

    /* Methods */
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

private:
    Vect get_normal(const Point3& point) const;

    /* Attributes */
    Point3 position;
};
