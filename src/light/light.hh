#pragma once

#include <memory>

#include "vector3.hh"

class Light {
public:

    Light() = default;

    virtual Vect get_light_position() const = 0;
    virtual Color get_light_color() const = 0;
    virtual double get_intensity() const = 0;

};

using shared_light = std::shared_ptr<Light>;
