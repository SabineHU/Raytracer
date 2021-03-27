#pragma once

#include "texture_material.hh"

class Lambertian : public TextureMaterial {
public:
    Lambertian() = default;
    Lambertian(const Color&);
    Lambertian(const Color&, double);

    virtual Color get_color(const Point3&, double, double) const override;

private:
    Color color;
};
