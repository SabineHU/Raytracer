#pragma once

#include "texture_material.hh"

class Unique : public TextureMaterial {
public:
    Unique() = default;
    Unique(const Color&);

    virtual Color get_color(double, double, double) const;

private:
    Color color;
};
