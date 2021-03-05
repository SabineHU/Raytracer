#include "sphere.hh"
#include "math.hh"
#include "vector3_op.hh"

Sphere::Sphere ()
    : center(Vect(0, 0, 0)), radius(1), color(Color(0.5, 0.5, 0.5, 0))
{}

Sphere::Sphere (Vect cent, double rad, Color col)
    : center(cent), radius(rad), color(col)
{}

Color Sphere::get_color() const {
    return color;
}

Vect Sphere::get_normal_at(Vect point) const {
    return (point - center).normalize();
}

double Sphere::find_intersection(Ray ray) const {
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
