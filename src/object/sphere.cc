#include "sphere.hh"
#include "math.hh"

Sphere::Sphere ()
    : center(Vect(0, 0, 0)), radius(1), color(Color(0.5, 0.5, 0.5, 0))
{}

Sphere::Sphere (Vect cent, double rad, Color col)
    : center(cent), radius(rad), color(col)
{}

Color Sphere::getColor() const {
    return color;
}

Vect Sphere::getNormalAt(Vect point) const {
    return (point - center).normalize();
}

double Sphere::findIntersection(Ray ray) const {
    auto oc = ray.getRayOrigin() - this->center;

    double a = 1; // normalized
    double b = 2 * oc.dotProduct(ray.getRayDirection());
    double c = oc.dotProduct(oc) - this->radius * this->radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant <= 0)
        return -1;

    double x1 = math::quadratic_equation_root_1(a, b, discriminant) - 0.000001;
    if (x1 > 0)
        return x1;
    return math::quadratic_equation_root_2(a, b, discriminant) - 0.000001;
}
