#include "light.hh"

Light::Light ()
    : position(Vect(0, 0, 0)), color(Color(1, 1, 1, 0))

{}

Light::Light (Vect p, Color c)
    : position(p), color(c)
{}

Vect Light::get_light_position() const {
    return this->position;
}

Color Light::get_light_color() const {
    return this->color;
}
