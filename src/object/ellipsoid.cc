#include "ellipsoid.hh"
#include "vector3_op.hh"
#include "unique.hh"

Ellipsoid::Ellipsoid()
    : center(Vect(0, 0, 0)), radius(Vect(1, 0.5, 1))
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Ellipsoid::Ellipsoid(const Vect& cent, const Vect& rad)
    : center(cent), radius(rad)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Ellipsoid::Ellipsoid(const Vect& cent, const Vect& rad, shared_texture t)
    : Object(t), center(cent), radius(rad)
{}

Ellipsoid::Ellipsoid(const Vect& cent, const Vect& rad, const Color& c)
    : Object(std::make_shared<Unique>(c)), center(cent), radius(rad)
{}

Vect Ellipsoid::get_normal_at(const Vect& point) const {
    return ((point - center) / radius).normalize();
}

bool Ellipsoid::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo&) {
    auto oc = ray.origin - this->center;

    Vect ocn = oc / this->radius;
    Vect rdn = ray.direction / this->radius;

    double a = rdn.square_length();
    double b = vector::dot(ocn, rdn);
    double c = ocn.square_length() - 1;

    double discriminant = b * b - a * c;
    if (discriminant < 0) return false;

    double t = (-b - std::sqrt(discriminant)) / a;
    if (t <= t_min || t >= t_max) return false;

    t_max = t;
    return true;
}

int Ellipsoid::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
