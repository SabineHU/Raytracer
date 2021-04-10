#include "plane.hh"
#include "vector3_op.hh"
#include "lambertian.hh"

Plane::Plane()
    : normal(Vect(1, 0, 0)), distance(0), height(1), width(1)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Lambertian>(color);
}

Plane::Plane(const Vect& n, double d)
    : normal(n), distance(d), height(1), width(1)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Lambertian>(color);
}

Vect Plane::get_normal_at(const Point3& point, double u, double v) const {
    auto bump = Object::get_bump_at(point);
    auto disp = Object::get_displacement_at(point, u, v);

    return ((normal + bump).normalize() + disp * 50).normalize();
}

bool Plane::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    double a = vector::dot(ray.direction, normal);
    if (a == 0) return false;

    double b = vector::dot(normal, ray.origin + normal * -distance);
    double x = - b / a;
    if (x <= t_min || x >= t_max)
        return false;
    t_max = x;

    info.point = ray.origin + ray.direction * t_max;
    info.u = info.point.x / width;
    info.v = info.point.z / height;

    return true;
}

int Plane::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
