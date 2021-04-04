#include "plane_holed.hh"
#include "vector3_op.hh"
#include "lambertian.hh"

PlaneHoled::PlaneHoled()
    : Plane(), scale_u(5), scale_v(5)
{}

PlaneHoled::PlaneHoled(const Vect& n, double d)
    : Plane(n, d), scale_u(5), scale_v(5)
{}

PlaneHoled::PlaneHoled(const Vect& n, double d, double u, double v)
    : Plane(n, d), scale_u(u), scale_v(v)
{}

bool PlaneHoled::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    double a = vector::dot(ray.direction, normal);
    if (a == 0) return false;

    double b = vector::dot(normal, ray.origin + normal * -distance);
    double x = - b / a;
    if (x <= t_min || x >= t_max) return false;

    info.point = ray.origin + ray.direction * x;
    info.u = info.point.x;
    info.v = info.point.z;

    int square = (int) std::floor(info.u * scale_u) + (int) std::floor(info.v * scale_v);
    if ((square % 2) == 0) return false;

    t_max = x;
    return true;
}
