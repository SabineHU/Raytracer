#include <cmath>

#include "cone.hh"
#include "math.hh"
#include "unique.hh"

Cone::Cone()
    : position(Point3(0, 0, 0)), radius(1), height(5)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Cone::Cone(const Point3& p, double r, double h)
    : position(p), radius(r), height(h)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Cone::Cone(const Point3& p, double r, double h, shared_texture t)
    : Object(t), position(p), radius(r), height(h)
{}

Vect Cone::get_normal_at(const Vect& point) const {
    float r = std::sqrt((point.x-position.x)*(point.x - position.x) + (point.z - position.z)*(point.z-position.z));
    Vect n = Vect(point.x-position.x, r*(radius/height), point.z-position.z);
    return n.normalize();
}

double Cone::find_intersection(const Ray& ray) const {

    double aa = ray.origin.x - this->position.x;
    double bb = ray.origin.z - this->position.z;
    double dd = height - ray.origin.y + this->position.y;

    double tan = this->radius * this->radius / (this->height * this->height);

    double a = ray.direction.dot_x() + ray.direction.dot_z()
        - tan * ray.direction.dot_y();
    double b = 2 * aa * ray.direction.x + 2 * bb * ray.direction.z
        + 2 * tan * dd * ray.direction.y;
    double c = aa * aa + bb * bb - tan * dd * dd;

    double discriminant = b * b - 4 * a * c;

    if (discriminant <= 0)
        return -1;

    double x = math::quadratic_equation_min_root(a, b, discriminant) - 0.000001;
    double r = ray.origin.y + ray.direction.y * x;
    if (r > position.y && r < position.y + height)
        return x;
    return -1;
}
