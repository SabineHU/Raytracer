#pragma once

#include "object.hh"
#include "vector3.hh"

class Plane : public Object {

public:
    Plane();

    Plane(Vect, double, Color);

    // method functions
    Vect getPlaneNormal () { return normal; }
    double getPlaneDistance () { return distance; }

    virtual Color getColor() const override;
    virtual Vect getNormalAt(Vect) const override;
    virtual double findIntersection(Ray ray) const override;

    /* Attributes */
    Vect normal;
    double distance;
    Color color;

};
