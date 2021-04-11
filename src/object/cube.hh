#pragma once

#include "object.hh"

class Cube : public Object {
public:
    Cube();
    Cube(const Point3&, double);

    /* Methods */
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const override;

private:
    /* Attributes */
    Point3 position; // lower left front
    double side;
};
