#pragma once

#include <memory>

#include "ray.hh"
#include "vector3.hh"

class Object {
public:
    Object() = default;

    virtual Color get_color() const = 0;
    virtual Vect get_normal_at(Vect intersection_position) const = 0;
    virtual double find_intersection(Ray ray) const = 0;

};

using shared_object = std::shared_ptr<Object>;
