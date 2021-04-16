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
    auto v = normal * vector::dot(normal, this->direction.negative());
    Vect res = (this->direction + v) * 2 - this->direction;

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
    // Snell Descartes law's
    // https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
    double cosi = std::max(-1.0, std::min(1.0, vector::dot(direction, normal)));
    Vect n;
    double n1, n2;
    if (cosi < 0) {
        cosi *= -1;
        n = normal;
        n2 = 1;
        n1 = ior;
    } else {
        n1 = 1;
        n2 = ior;
        n = normal.negative();
    }
    double n2n1 = n2 / n1;
    double k = 1 - n2n1 * n2n1 * (1 - cosi * cosi);
    if (k < 0) return Vect(0, 0, 0);
    return (direction * n2n1 + n * (n2n1 * cosi - sqrtf(k))).normalize();
}
