#pragma once

#include "object.hh"

class Rectangle_xz : public Object {
public:
    Rectangle_xz();
    Rectangle_xz(const Vect&, const Vect&);

    /* Methods */
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const override;

private:
    /* Attributes */
    Vect p1; // lower left
    Vect p2; // top right

    Vect normal;
};
