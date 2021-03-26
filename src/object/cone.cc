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

Cone::Cone(const Point3& p, double r, double h, const Color& c)
    : Object(std::make_shared<Unique>(c)), position(p), radius(r), height(h)
{}

Vect Cone::get_normal_at(const Vect& point) const {
    // center of cone and intersection point vector
    Vect PP = point - this->position;
    double r = std::sqrt(PP.dot_x() + PP.dot_z());
    return Vect(PP.x, r * this->radius / this->height, PP.z).normalize();
}

bool Cone::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo&) {
    const Vect dir = ray.direction;

    // Position Origin vector
    Vect PO = ray.origin - this->position;
    PO *= Vect(1, -1, 1);
    PO += Vect(0, height, 0);

    double tan = this->radius * this->radius / (this->height * this->height);

    double a = dir.dot_x() + dir.dot_z() - tan * dir.dot_y();
    double b = (PO * dir * Vect(1, tan, 1) * 2).sum();
    double c = PO.dot_x() + PO.dot_z() - tan * PO.dot_y();

    double discriminant = b * b - 4 * a * c;
    if (discriminant <= 0) return false;

    double x = math::quadratic_equation_min_root(a, b, discriminant) - 0.000001;
    double r = ray.origin.y + ray.direction.y * x;
    if (r <= position.y || r >= position.y + height)
        return false;

    if (x <= t_min || x >= t_max) return false;

    t_max = x;
    return true;
}

int Cone::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
