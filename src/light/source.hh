#pragma once

#include <memory>

#include "vector3.hh"

class Source {
public:

    Source() = default;

    virtual Vect getLightPosition() const = 0;
    virtual Color getLightColor() const = 0;

};

using shared_light = std::shared_ptr<Source>;
