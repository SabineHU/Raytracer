#pragma once

#include "ray.hh"
#include "vector3.hh"

class Object {
public:
    Object() = default;

    virtual Color getColor() const = 0;
    virtual Vect getNormalAt(Vect intersection_position) const = 0;
    virtual double findIntersection(Ray ray) const = 0;

};
