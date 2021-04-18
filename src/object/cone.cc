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

Vect Cone::get_normal(const Point3& point) const {
    // center of cone and intersection point vector
    Vect PP = point - this->position;
    double r = std::sqrt(PP.dot_x() + PP.dot_z());

    return Vect(PP.x, r * this->radius / this->height, PP.z);
}

static void compute_uv(IntersectionInfo& info, double dist) {
    info.u = 0.5 + atan2(info.point.x, info.point.y) / (2 * math::pi);
    info.v = -info.point.z / dist;
}

bool Cone::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const {
    // Equation over z-axis is x^2 + y^2 = z^2

    // Position Origin vector
    Vect PO = (ray.origin - this->position) * Vect(1, -1, 1) + Vect(0, height, 0);
    double angle = this->radius * this->radius / (this->height * this->height);

    double a = ray.direction.dot_x() + ray.direction.dot_z() - angle * ray.direction.dot_y();
    double b = (PO * ray.direction * Vect(1, angle, 1)).sum();

    double discriminant = b * b - a * (PO.dot_x() + PO.dot_z() - angle * PO.dot_y());
    if (discriminant <= 0) return false;
    discriminant = std::sqrt(discriminant);

    double roots[2] = { (-b - discriminant) / a, (-b + discriminant) / a };
    b = roots[0]; // min root
    a = ray.origin.y + ray.direction.y * b;
    if (a <= position.y || a >= position.y + height || b <= t_min || b >= t_max)
        return false;

    t_max = b;
    info.point = ray.origin + ray.direction * t_max;
    compute_uv(info, this->height);

    info.t_min = roots[0];
    info.t_max = roots[1];

    info.normal = this->get_normal(info.point);
    this->get_properties(info);

    return true;
}
