#pragma once

#include <memory>

#include "vector3.hh"

enum MaterialType {
    DIFFUSE,
    DIFFUSE_GLOSSY,
    REFLECTION,
    REFLECTION_REFRACTION
};

class TextureMaterial {
public:
    TextureMaterial() : specular(0), type(DIFFUSE) {}
    TextureMaterial(double s) : specular(s), type(DIFFUSE) {}

    virtual Color get_color(const Point3&, double, double) const = 0;

    double specular; //ks
    MaterialType type = DIFFUSE;
};

using shared_texture = std::shared_ptr<TextureMaterial>;
