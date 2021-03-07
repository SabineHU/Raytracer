#include "ray.hh"
#include "vector3_op.hh"

Ray::Ray()
    : origin(Vect(0, 0, 0)), direction(Vect(1, 0, 0))
{}

Ray::Ray (const Vect& o, const Vect& d)
    : origin(o), direction(d)
{}

Ray Ray::get_reflection_ray(const Vect& normal) const {
    double dot1 = vector::dot(normal, this->direction.negative());
    Vect scalar1 = normal * dot1;
    Vect add1 = scalar1 + this->direction;
    Vect scalar2 = add1 * 2;
    Vect add2 = scalar2 - this->direction;
    Vect reflection_direction = add2.normalize();

    return Ray(this->origin, reflection_direction);
}

Point3 Ray::at(double i) const {
    return this->origin + this->direction * i;
}
