#pragma once

#include "object.hh"
#include "vector3.hh"

class Plane : public Object {
public:
    Plane();
    Plane(const Vect&, double, const Color&);
    Plane(const Vect&, double, const Color&, shared_texture);
    Plane(const Vect&, double, const Color&, shared_texture, double);

    /* Methods */
    virtual Color get_color() const override;
    virtual Vect get_normal_at(const Vect&) const override;
    virtual double find_intersection(const Ray& ray) const override;

    /* Attributes */
    Vect normal;
    double distance;
    Color color;
};
