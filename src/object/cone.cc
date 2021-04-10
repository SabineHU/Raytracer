#include <cmath>

#include "cone.hh"
#include "math.hh"
#include "lambertian.hh"

Cone::Cone()
    : Object(), position(Point3(0, 0, 0)), radius(1), height(5)
{}

Cone::Cone(const Point3& p, double r, double h)
    : Object(), position(p), radius(r), height(h)
{}

Vect Cone::get_normal_at(const Point3& point, double, double) const {
    // center of cone and intersection point vector
    Vect PP = point - this->position;
    double r = std::sqrt(PP.dot_x() + PP.dot_z());

    return (Vect(PP.x, r * this->radius / this->height, PP.z) + Object::get_bump_at(point)).normalize();
}

static void compute_uv(IntersectionInfo& info, double dist) {
    info.u = 0.5 + atan2(info.point.x, info.point.y) / (2 * math::pi);
    info.v = -info.point.z / dist;
}

bool Cone::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
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

    double roots[2] = { -1 };
    math::quadratic_equation_roots(a, b, discriminant, roots);

    double x = roots[0];
    double r = ray.origin.y + ray.direction.y * x;
    if (r <= position.y || r >= position.y + height)
        return false;

    if (x <= t_min || x >= t_max) return false;

    t_max = x;
    info.point = ray.origin + ray.direction * t_max;
    compute_uv(info, this->height);

    info.t_min = roots[0];
    info.t_max = roots[1];

    return true;
}

int Cone::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
