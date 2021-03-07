#pragma once

#include "texture_material.hh"

class Unique : public TextureMaterial {
public:
    Unique() = default;
    Unique(const Color&);

    virtual Color get_color(const Ray&) const override;

private:
    Color color;
};
