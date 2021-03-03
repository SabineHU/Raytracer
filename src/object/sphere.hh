#pragma once

#include "object.hh"
#include "vector3.hh"

class Sphere : public Object {
public:

    Sphere();
    Sphere(Vect, double, Color);

    Vect getSphereCenter () { return center; }
    double getSphereRadius () { return radius; }

    virtual Color getColor() const override;
    virtual Vect getNormalAt(Vect point) const override;
    virtual double findIntersection(Ray ray) const override;

    /* Attribute */
    Vect center;
    double radius;
    Color color;


};

