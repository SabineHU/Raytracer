#include <algorithm>

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

Vect Ray::get_reflection_dir(const Vect& normal) const {
    return (direction - normal * vector::dot(direction, normal) * 2).normalize();
}

Vect Ray::get_refraction_dir(const Vect& normal, double ior) const {
    double cosi = std::max(-1.0, std::min(1.0, vector::dot(direction, normal)));
    double etai = 1;
    double etat = ior;
    Vect n;
    if (cosi < 0) {
        cosi *= -1;
        n = normal;
    } else {
        std::swap(etai, etat);
        n = normal.negative();
    }
    double eta = etai / etat;
    double k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? Vect(0, 0, 0) : (direction * eta + n * (eta * cosi - sqrtf(k))).normalize();
}
