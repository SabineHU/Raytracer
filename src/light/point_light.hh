#pragma once

#include "light.hh"
#include "vector3.hh"

class PointLight : public Light {
public:

    PointLight();
    PointLight(const Vect&, const Color&);
    PointLight(const Vect&, const Color&, double);

    virtual Vect get_light_position() const override;
    virtual Color get_light_color() const override;
    virtual double get_intensity() const override;

    Vect position;
    Color color;
    double intensity;

};
