#pragma once

#include <memory>

#include "vector3.hh"

enum MaterialType: int {
    DIFFUSE = 1,
    REFLECTION = 1 << 1,
    REFRACTION = 1 << 2,
    TRANSPARENT = 1 << 3
};

class TextureMaterial {
public:
    TextureMaterial() : ka(0.5), kd(0.5), ks(0.5), kt(0.5), type(DIFFUSE) {}

    TextureMaterial(double d, double s)
        : ka(0.5), kd(d), ks(s), kt(0.5), type(DIFFUSE) {}

    TextureMaterial(double a, double d, double s)
        : ka(a), kd(d), ks(s), kt(0.5), type(DIFFUSE) {}

    virtual Color get_color(const Point3&, double, double) const = 0;

    /* Setters / Add */
    void set_diffuse_type() { type = DIFFUSE; }
    void add_diffuse_type() { type |= DIFFUSE; }

    void set_reflection_type() { type = REFLECTION; }
    void add_reflection_type() { type |= REFLECTION; }

    void set_refraction_type() { type = REFRACTION; }
    void add_refraction_type() { type |= REFRACTION; }

    void set_transparent_type() { type = REFLECTION | REFRACTION | TRANSPARENT; }

    /* Attributes */
    double ka, kd, ks, kt;
    double attenuation = 1;
    int type = DIFFUSE;
};

using shared_texture = std::shared_ptr<TextureMaterial>;
