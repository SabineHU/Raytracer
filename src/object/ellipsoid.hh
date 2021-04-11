#pragma once

#include "object.hh"

class Ellipsoid : public Object {
public:

    Ellipsoid();
    Ellipsoid(const Vect&, const Vect&);

    /* Methods */
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const override;

private:
    Vect get_normal(const Point3& point) const;

    /* Attributes */
    Vect center;
    Vect radius;
};
