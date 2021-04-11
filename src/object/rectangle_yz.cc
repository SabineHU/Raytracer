#include "rectangle_yz.hh"
#include "vector3_op.hh"

Rectangle_yz::Rectangle_yz()
    : p1(Vect(0, 0, 0)), p2(Vect(1, 1, 0))
{}

Rectangle_yz::Rectangle_yz(const Vect& u, const Vect& v)
    : p1(u), p2(v)
{}

bool Rectangle_yz::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    double t = (this->p1.x - ray.origin.x) / ray.direction.x;
    if (t <= t_min || t >= t_max) return false;

    Vect p = ray.origin + ray.direction * t;
    bool hit = p.y <= this->p2.y && p.y >= this->p1.y &&
        p.z <= this->p2.z && p.z >= this->p1.z;

    if (hit) {
        t_max = t;
        info.point = p;
        info.normal = Vect(1, 0, 0);
        if (vector::dot(ray.direction, info.normal) > 0)
            info.normal = info.normal.negative();

        info.u = (p.y - p1.y) / (p2.y - p1.y);
        info.v = (p.z - p1.z) / (p2.z - p1.z);

        return true;
    }

    return false;
}
