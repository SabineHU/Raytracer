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

    virtual Color get_color() const override;
    virtual Vect get_normal_at(const Vect&) const override;
    virtual double find_intersection(const Ray& ray) const override;

    /* Attributes */
    Vect normal;
    double distance;
    Color color;

};
