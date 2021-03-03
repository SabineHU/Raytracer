#pragma once

#include "ray.hh"
#include "vector3.hh"

class Object {
public:
    Object() = default;

    virtual Color getColor() = 0;

    virtual Vect getNormalAt(Vect intersection_position) = 0;

    virtual double findIntersection(Ray ray) = 0;

};
