#pragma once

#include <memory>

#include "vector3.hh"

class TextureMaterial {
public:
    virtual Color get_color(double, double, double) const = 0;
};

using shared_texture = std::shared_ptr<TextureMaterial>;
