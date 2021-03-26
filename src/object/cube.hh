#pragma once

#include "object.hh"

class Cube : public Object {
public:
    Cube();
    Cube(const Point3&, double, shared_texture);
    Cube(const Point3&, double, const Color&);

    /* Methods */
    virtual Vect get_normal_at(const Vect& point) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

    virtual int get_isolevel_at(const Point3&) const override;

private:
    /* Attributes */
    Point3 position; // lower left front
    double side;

    Vect normal;
};
