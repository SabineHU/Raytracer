#pragma once

#include "object.hh"

class Ellipsoid : public Object {
public:

    Ellipsoid();
    Ellipsoid(const Vect&, const Vect&);
    Ellipsoid(const Vect&, const Vect&, shared_texture);
    Ellipsoid(const Vect&, const Vect&, const Color&);

    /* Methods */
    virtual Vect get_normal_at(const Vect& point) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max) override;

    virtual int get_isolevel_at(const Point3&) const override;

    /* Attribute */
    Vect center;
    Vect radius;
};