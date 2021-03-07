#include "light.hh"

Light::Light ()
    : position(Vect(0, 0, 0)), color(Color(1, 1, 1)), intensity(1)

{}

Light::Light (const Vect& p, const Color& c)
    : position(p), color(c), intensity(1)
{}

Light::Light (const Vect& p, const Color& c, double i)
    : position(p), color(c), intensity(i)
{}

Vect Light::get_light_position() const {
    return this->position;
}

Color Light::get_light_color() const {
    return this->color;
}

double Light::get_intensity() const {
    return this->intensity;
}
