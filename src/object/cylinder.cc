#include "cylinder.hh"
#include "math.hh"
#include "unique.hh"

Cylinder::Cylinder()
    : center(Point3(0, 0, 0)), radius(1), height(1)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Cylinder::Cylinder(const Point3& p, double r, double h)
    : center(p), radius(r), height(h)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Cylinder::Cylinder(const Point3& p, double r, double h, shared_texture t)
    : Object(t), center(p), radius(r), height(h)
{}

Cylinder::Cylinder(const Point3& p, double r, double h, const Color& c)
    : Object(std::make_shared<Unique>(c)), center(p), radius(r), height(h)
{}

Vect Cylinder::get_normal_at(const Vect& point) const {
    return Vect(point.x - center.x, 0, point.z - center.z).normalize();
}

bool Cylinder::find_intersection(const Ray& ray, double& t_min, double& t_max) {

    Vect PO = Vect(ray.origin.x - center.x, 0, ray.origin.z - center.z);

    // d0 = y
    // d1 = x
    // d2 = z
    double a = ray.direction.dot_x() + ray.direction.dot_z();
    double b = 2 * (ray.direction.x * PO.x + ray.direction.z * PO.z);
    double c = PO.dot_x() + PO.dot_z() - this->radius * this->radius;

    double discriminant = b * b - 4 * a * c;
    if (discriminant <= 0) {
        return false;
    }

    double x = math::quadratic_equation_min_root(a, b, discriminant) - 0.000001;
    double r = ray.origin.y + ray.direction.y * x;
    if (r < this->center.y || r > this->center.y + height)
        return false;

    if (x <= t_min || x >= t_max) return false;

    t_max = x;
    return true;
}

int Cylinder::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
