#pragma once

#include "plane.hh"

class PlaneHoled : public Plane {
public:
    PlaneHoled();
    PlaneHoled(const Vect& n, double d);
    PlaneHoled(const Vect& n, double d, double u, double v);

    /* Methods */
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

private:
    double scale_u;
    double scale_v;
};
