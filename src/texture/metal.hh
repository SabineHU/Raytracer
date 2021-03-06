#pragma once

#include "texture_material.hh"

class Metal : public TextureMaterial {
public:
    Metal() = default;
    Metal(const Color&);

    virtual Color get_color(double, double, double) const override;

private:
    Color color;
};
