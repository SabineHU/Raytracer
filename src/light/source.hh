#pragma once

#include "vector3.hh"

class Source {
public:

    Source() = default;

    virtual Vect getLightPosition() const = 0;
    virtual Color getLightColor() const = 0;

};
