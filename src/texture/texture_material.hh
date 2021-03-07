#pragma once

#include <memory>

#include "vector3.hh"
#include "ray.hh"

class TextureMaterial {
public:

    virtual Color get_color(const Ray&) const = 0;
};

using shared_texture = std::shared_ptr<TextureMaterial>;
