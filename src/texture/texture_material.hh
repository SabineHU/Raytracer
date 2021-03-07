#pragma once

#include <memory>

#include "vector3.hh"
#include "ray.hh"

class TextureMaterial {
public:
    TextureMaterial(double s) : specular(s) {}

    virtual Color get_color(const Ray&, const Vect&) const = 0;

    double specular; //ks
};

using shared_texture = std::shared_ptr<TextureMaterial>;
