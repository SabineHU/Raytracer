#pragma once

#include "object.hh"
#include "vector3.hh"

class Plane : public Object {
public:
    Plane();
    Plane(const Vect&, double);

    /* Methods */
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const override;

    void set_height(double h) { height = h; }
    void set_width(double w) { width = w; }

protected:
    /* Attributes */
    Vect normal;
    double distance;

    double height;
    double width;
};
