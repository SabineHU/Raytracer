#pragma once

#include "texture_material.hh"

class Unique : public TextureMaterial {
public:
    Unique() = default;
    Unique(const Color&);
    Unique(const Color&, double);

    virtual Color get_color(const Ray&, const Vect&) const override;

private:
    Color color;
};
