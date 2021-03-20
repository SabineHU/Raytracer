#pragma once

#include <memory>

#include "ray.hh"
#include "vector3.hh"
#include "texture_material.hh"

class Object {
public:
    Object() = default;
    Object(shared_texture t) : texture(t) {}

    /* Methods */
    virtual Vect get_normal_at(const Vect& point) const = 0;
    virtual double find_intersection(const Ray& ray) = 0;

    virtual int get_isolevel_at(const Point3&) const = 0;

    /* Attributes */
    shared_texture texture;
};


using shared_object = std::shared_ptr<Object>;
