#include "rectangle_xy.hh"
#include "vector3_op.hh"

Rectangle_xy::Rectangle_xy()
    : p1(Vect(0, 0, 0)), p2(Vect(1, 1, 0))
{}

Rectangle_xy::Rectangle_xy(const Vect& u, const Vect& v)
    : p1(u), p2(v)
{}

bool Rectangle_xy::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const {
    double t = (this->p1.z - ray.origin.z) / ray.direction.z;
    if (t <= t_min || t >= t_max) return false;

    Vect p = ray.origin + ray.direction * t;
    bool hit = p.x <= this->p2.x && p.x >= this->p1.x &&
        p.y <= this->p2.y && p.y >= this->p1.y;

    if (!hit) return false;

    t_max = t;
    info.point = p;
    info.normal = Vect(0, 0, 1);
    if (vector::dot(ray.direction, info.normal) > 0)
        info.normal = info.normal.negative();

    info.u = (p.x - p1.x) / (p2.x - p1.x);
    info.v = (p.y - p1.y) / (p2.y - p1.y);
    this->get_properties(info);

    return true;
}
