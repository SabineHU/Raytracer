#include "cube.hh"
#include "lambertian.hh"
#include "tools.hh"

Cube::Cube()
    : Object(), position(Point3(0, 0, 0)), side(1), normal(Vect())
{}

Cube::Cube(const Point3& p, double s)
    : Object(), position(p), side(s), normal(Vect())
{}

Vect Cube::get_normal_at(const Point3& point, double, double) const {
    return (normal + Object::get_bump_at(point)).normalize();
}

static bool compute_axis(double& max, double& min, double& max_v, double& min_v,
        Vect& nmax, Vect& nmin, int axis) {
    Vect nmin_v = Vect(0, -1, 0);
    Vect nmax_v = Vect(0, 1, 0);

    if (axis == 2) {
        nmin_v = Vect(0, 0, -1);
        nmax_v = Vect(0, 0, 1);
    }

    tools::swap_min(max_v, min_v, nmin_v, nmax_v);
    if (max < min_v || max_v < min) return false;

    tools::get_max(min_v, min, nmin_v, nmin);
    tools::get_min(max_v, max, nmax_v, nmax);
    return true;
}

bool Cube::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    const Vect r_dir = Vect(1, 1, 1) / ray.direction;

    Vect min_v = (position - ray.origin) * r_dir;
    Vect max_v = (position + Vect(side, side, side) - ray.origin) * r_dir;

    double min = min_v.x;
    double max = max_v.x;

    /* Normal x axis */
    Vect nmin(-1, 0, 0);
    Vect nmax(1, 0, 0);
    tools::swap_min(max, min, nmin, nmax);

    /* Normal y axis */
    if (!compute_axis(max, min, max_v.y, min_v.y, nmax, nmin, 1))
        return false;

    /* Normal z axis */
    if (!compute_axis(max, min, max_v.z, min_v.z, nmax, nmin, 2))
        return false;

    /* Get the second solution if first one is negative */
    tools::modify_if_negative(min, max, nmin, nmax);
    if (min < 0) {
        min = max;
        nmin = nmax;
    }
    if (min < 0 || min < t_min || min >= t_max) return false;

    info.t_max = max;
    info.t_min = min;

    t_max = min;
    this->normal = nmin;
    info.point = ray.origin + ray.direction * t_max;
    info.normal = nmin;

    auto OP = (info.point - position) / side;
    if(std::fabs(nmin.z) > std::fabs(nmin.x)
            && std::fabs(nmin.z) > std::fabs(nmin.y)) {
        info.u = OP.x;
        info.v = OP.y;
    } else if(std::fabs(nmin.y) > std::fabs(nmin.x)) {
        info.u = OP.x;
        info.v = OP.z;
    } else {
        info.u = OP.y;
        info.v = OP.z;
    }

    return true;
}

int Cube::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
