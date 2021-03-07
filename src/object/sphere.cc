#include "sphere.hh"
#include "math.hh"
#include "vector3_op.hh"
#include "unique.hh"

Sphere::Sphere()
    : center(Vect(0, 0, 0)), radius(1)
{
    auto color = Color(0.5, 0.5, 0.5, 0);
    texture = std::make_shared<Unique>(color);
    specular = 0;
}

Sphere::Sphere(const Vect& cent, double rad)
    : center(cent), radius(rad)
{
    auto color = Color(0.5, 0.5, 0.5, 0);
    texture = std::make_shared<Unique>(color);
    specular = 0;
}

Sphere::Sphere(const Vect& cent, double rad, shared_texture t)
    : Object(t, 0), center(cent), radius(rad)
{}

Sphere::Sphere(const Vect& cent, double rad, shared_texture t,
        double s)
    : Object(t, s), center(cent), radius(rad)
{}

Vect Sphere::get_normal_at(const Vect& point) const {
    return (point - center).normalize();
}

double Sphere::find_intersection(const Ray& ray) const {
    auto oc = ray.origin - this->center;

    double a = 1; // normalized
    double b = 2 * vector::dot(oc, ray.direction);
    double c = vector::dot(oc, oc) - this->radius * this->radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant <= 0)
        return -1;

    double x1 = math::quadratic_equation_root_1(a, b, discriminant) - 0.000001;
    if (x1 > 0)
        return x1;
    return math::quadratic_equation_root_2(a, b, discriminant) - 0.000001;
}
