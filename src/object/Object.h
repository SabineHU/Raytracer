#ifndef _OBJECT_H
#define _OBJECT_H

#include "Ray.h"
#include "vector3.hh"

class Object {
public:
    Object () = default;

    virtual Color getColor() = 0;

    virtual Vect getNormalAt(Vect intersection_position) = 0;

    virtual double findIntersection(Ray ray) = 0;

};

#endif
