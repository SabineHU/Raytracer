#pragma once

#include "texture_material.hh"

class Metal : public TextureMaterial {
public:
    Metal() = default;
    Metal(const Color&);
    Metal(const Color&, double);

    virtual Color get_color(const Ray&, const Vect&) const override;

private:
    Color color;
};
