#include <cmath>

#include "sphere.hh"
#include "math.hh"
#include "vector3_op.hh"
#include "unique.hh"

Sphere::Sphere()
    : center(Vect(0, 0, 0)), radius(1)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Sphere::Sphere(const Vect& cent, double rad)
    : center(cent), radius(rad)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Sphere::Sphere(const Vect& cent, double rad, shared_texture t)
    : Object(t), center(cent), radius(rad)
{}

Sphere::Sphere(const Vect& cent, double rad, const Color& c)
    : Object(std::make_shared<Unique>(c)), center(cent), radius(rad)
{}

Vect Sphere::get_normal_at(const Vect& point) const {
    return (point - center).normalize();
}

double Sphere::find_intersection(const Ray& ray) {
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

bool Sphere::find_intersection2(const Ray& ray, double& t_min, double& t_max) {
    auto oc = ray.origin - this->center;

    double a = 1; // normalized
    double b = 2 * vector::dot(oc, ray.direction);
    double c = vector::dot(oc, oc) - this->radius * this->radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant <= 0) return false;

    double x1 = math::quadratic_equation_root_1(a, b, discriminant) - 0.000001;
    if (x1 > 0) {
        if (x1 <= t_min || x1 >= t_max) return false;
        t_max = x1;
        return true;
    }

    x1 = math::quadratic_equation_root_2(a, b, discriminant) - 0.000001;
    if (x1 <= t_min || x1 >= t_max) return false;
    t_max = x1;
    return true;
}

int Sphere::get_isolevel_at(const Point3& point) const {
    double distance = (point - this->center).square_length();
    if (distance > 4 * radius * radius)
        return 100;

    for (int i = 199; i > 100; i-=1) {
        if (distance > (radius * i / 100) * (radius * i / 100))
            return i - 100;
    }
    return 0;
}
