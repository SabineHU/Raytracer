#pragma once

#include <memory>

#include "ray.hh"
#include "vector3.hh"
#include "texture_material.hh"

class Object {
public:
    Object() = default;
    Object(shared_texture t) : texture(t), specular(0) {}
    Object(shared_texture t, double s) : texture(t), specular(s) {}

    /* Methods */
    virtual Vect get_normal_at(const Vect& intersection_position) const = 0;
    virtual double find_intersection(const Ray& ray) const = 0;

    /* Attributes */
    shared_texture texture;
    double specular;
};

using shared_object = std::shared_ptr<Object>;
