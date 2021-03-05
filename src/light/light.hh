#pragma once

#include "source.hh"
#include "vector3.hh"

class Light : public Source {
public:

    Light();
    Light(Vect, Color);

    virtual Vect get_light_position() const override;
    virtual Color get_light_color() const override;

    Vect position;
    Color color;
};
