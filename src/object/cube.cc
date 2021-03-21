#include "cube.hh"
#include "unique.hh"

Cube::Cube()
    : position(Point3(0, 0, 0)), side(1), normal(Vect())
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Cube::Cube(const Point3& p, double s, shared_texture t)
    : Object(t), position(p), side(s), normal(Vect())
{}

Cube::Cube(const Point3& p, double s, const Color& c)
    : Object(std::make_shared<Unique>(c)), position(p), side(s), normal(Vect())
{}

Vect Cube::get_normal_at(const Vect&) const {
    return normal;
}

bool Cube::find_intersection(const Ray& ray, double& t_min, double& t_max) {

    Vect r_dir = Vect(1, 1, 1) / ray.direction;
    Point3 bmax = position + Vect(side, side, side);

    // Get the intersection interval for the near and far x planes
    double tmin = (this->position.x - ray.origin.x) * r_dir.x;
    double tmax = (bmax.x - ray.origin.x) * r_dir.x;
    Vect nmin(-1.0, 0.0, 0.0);
    Vect nmax(1.0, 0.0, 0.0);

    // Swap if txmax is closer than txmin
    if(tmax < tmin)
    {
        std::swap<double>(tmin, tmax);
        nmin = Vect(1.0, 0.0, 0.0);
        nmax = Vect(-1.0, 0.0, 0.0);
    }

    // Get the intersection interval for the near and far y planes
    double tymin = (this->position.y - ray.origin.y) * r_dir.y;
    double tymax = (bmax.y - ray.origin.y) * r_dir.y;
    Vect nymin(0.0, -1.0, 0.0);
    Vect nymax(0.0, 1.0, 0.0);

    // Swap if tymax is closer than tymin
    if(tymax < tymin)
    {
        std::swap<double>(tymin, tymax);
        nymin = Vect(0.0, 1.0, 0.0);
        nymax = Vect(0.0, -1.0, 0.0);
    }

    // Now if the intervals don't overlap then the ray does not intersect at all
    if(tmax < tymin || tymax < tmin) return false;

    // Now tmin is the max of tmin and tymin (i.e. the interval is closer to the true intersection point)
    if(tymin > tmin)
    {
        tmin = tymin;
        nmin = nymin;
    }

    // tmax is the min of tmax and tymax
    if(tymax < tmax)
    {
        tmax = tymax;
        nmax = nymax;
    }

    // Get the intersection interval for the near and far z planes
    double tzmin = (this->position.z - ray.origin.z) * r_dir.z;
    double tzmax = (bmax.z - ray.origin.z) * r_dir.z;
    Vect nzmin(0.0, 0.0, -1.0);
    Vect nzmax(0.0, 0.0, 1.0);

    // Swap if tzmax is closer than tzmin
    if(tzmax < tzmin)
    {
        std::swap<double>(tzmin, tzmax);
        nzmin = Vect(0.0, 0.0, 1.0);
        nzmax = Vect(0.0, 0.0, -1.0);
    }

    // If the intervals don't overlap, well the ray doesn't intersect at all
    if(tmax < tzmin || tzmax < tmin) return false;

    // Take the max of the two min intersection intervals
    if(tzmin > tmin)
    {
        tmin = tzmin;
        nmin = nzmin;
    }

    // Take the min of the two max intersection intervals
    if(tzmax < tmax)
    {
        tmax = tzmax;
        nmax = nzmax;
    }

    // Check if both intersection distances are less than 0. The intersection point is then behind the ray's origin
    // If only tmin is less than 0, then the ray originates from within the box and we take tmax as the intersection interval
    double t = tmin;
    Vect n = nmin;
    if(tmin < 0)
    {
        t = tmax;
        n = nmax;
    }

    if (t < 0 || t < t_min || t >= t_max) return false;

    this->normal = n;
    t_max = t;
    return true;
}

int Cube::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
