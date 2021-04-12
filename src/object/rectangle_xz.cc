#include "rectangle_xz.hh"
#include "vector3_op.hh"

Rectangle_xz::Rectangle_xz()
    : p1(Vect(0, 0, 0)), p2(Vect(1, 1, 0))
{}

Rectangle_xz::Rectangle_xz(const Vect& u, const Vect& v)
    : p1(u), p2(v)
{}

bool Rectangle_xz::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const {
    double t = (this->p1.y - ray.origin.y) / ray.direction.y;
    if (t <= t_min || t >= t_max) return false;

    Vect p = ray.origin + ray.direction * t;
    bool hit = p.x <= this->p2.x && p.x >= this->p1.x &&
        p.z <= this->p2.z && p.z >= this->p1.z;

    if (!hit) return false;

    t_max = t;
    info.point = p;
    info.normal = Vect(0, 1, 0);
    if (vector::dot(ray.direction, info.normal) > 0)
        info.normal = info.normal.negative();

    info.u = (p.x - p1.x) / (p2.x - p1.x);
    info.v = (p.z - p1.z) / (p2.z - p1.z);
    this->get_properties(info);

    return true;
}
