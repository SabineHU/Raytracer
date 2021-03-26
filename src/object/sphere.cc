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

bool Sphere::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    auto oc = ray.origin - this->center;

    //double a = 1; // normalized
    double b = 2 * vector::dot(oc, ray.direction);
    double c = vector::dot(oc, oc) - this->radius * this->radius;

    double discriminant = b * b - 4 * c;

    if (discriminant <= 0) return false;

    double x = math::quadratic_equation_min_root(1, b, discriminant);
    if (x <= t_min || x >= t_max) return false;

    t_max = x;
    info.point = ray.origin + ray.direction * x;
    info.normal = this->get_normal_at(info.point);

    info.u = 0.5 + atan2(-info.normal.z, info.normal.x) / (2 * math::pi);
    info.v = 0.5 - asin(info.normal.y) / math::pi;

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
