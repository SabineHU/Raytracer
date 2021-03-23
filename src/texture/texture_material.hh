#pragma once

#include <memory>

#include "vector3.hh"
#include "ray.hh"

enum MaterialType {
    DIFFUSE,
    DIFFUSE_GLOSSY,
    REFLECTION,
    REFLECTION_REFRACTION
};

class TextureMaterial {
public:
    TextureMaterial(double s) : specular(s), type(DIFFUSE) {}

    virtual Color get_color(const Ray&, const Vect&) const = 0;

    double specular; //ks
    MaterialType type;
};

using shared_texture = std::shared_ptr<TextureMaterial>;
