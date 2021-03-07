#pragma once

#include "source.hh"
#include "vector3.hh"

class Light : public Source {
public:

    Light();
    Light(const Vect&, const Color&);
    Light(const Vect&, const Color&, double);

    virtual Vect get_light_position() const override;
    virtual Color get_light_color() const override;
    virtual double get_intensity() const override;

    Vect position;
    Color color;
    double intensity;

};
