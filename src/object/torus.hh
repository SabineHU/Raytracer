#pragma once

#include "object.hh"

class Torus : public Object {
public:

    Torus();
    Torus(const Point3&);
    Torus(const Point3&, shared_texture);
    Torus(const Point3&, const Color&);

    /* Methods */
    virtual Vect get_normal_at(const Vect& point) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max) override;

    virtual int get_isolevel_at(const Point3&) const override;

private:
    /* Attributes */
    Point3 position;
};
