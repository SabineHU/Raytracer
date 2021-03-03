#pragma once

#include "source.hh"
#include "vector3.hh"

class Light : public Source {
public:

    Light();
    Light(Vect, Color);

    virtual Vect getLightPosition() const override;
    virtual Color getLightColor() const override;

    Vect position;
    Color color;
};
