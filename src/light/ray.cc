#include "ray.hh"
#include "vector3_op.hh"

Ray::Ray()
    : origin(Vect(0, 0, 0)), direction(Vect(1, 0, 0))
{}

Ray::Ray (const Vect& o, const Vect& d)
    : origin(o), direction(d)
{}

Ray Ray::get_reflection_ray(const Vect& normal) const {
    auto prod = normal * vector::dot(normal, this->direction.negative());
    Vect add = (this->direction + prod) * 2;
    Vect res = add - this->direction;

    Vect reflection_direction = res.normalize();
    return Ray(this->origin, reflection_direction);
}

Point3 Ray::at(double i) const {
    return this->origin + this->direction * i;
}
