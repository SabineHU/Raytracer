#pragma once

#include <memory>

#include "vector3.hh"

enum MaterialType: int {
    DIFFUSE = 1,
    REFLECTION = 1 << 1,
    REFRACTION = 1 << 2
};

class TextureMaterial {
public:
    TextureMaterial() : specular(0), type(DIFFUSE) {}
    TextureMaterial(double s) : specular(s), type(DIFFUSE) {}

    virtual Color get_color(const Point3&, double, double) const = 0;

    void set_diffuse_type() { type = DIFFUSE; }
    void add_diffuse_type() { type |= DIFFUSE; }

    void set_reflection_type() { type = REFLECTION; }
    void add_reflection_type() { type |= REFLECTION; }

    void set_refraction_type() { type = REFRACTION; }
    void add_refraction_type() { type |= REFRACTION; }

    double specular;
    int type = DIFFUSE;
};

using shared_texture = std::shared_ptr<TextureMaterial>;
