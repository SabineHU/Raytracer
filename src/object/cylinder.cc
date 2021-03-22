#include "cylinder.hh"
#include "math.hh"
#include "unique.hh"
#include "vector3_op.hh"

Cylinder::Cylinder()
    : bottom(Point3(0, 0, 0)), top(Point3(0, 1, 0)), radius(1)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Cylinder::Cylinder(const Point3& b, const Point3& t, double r)
    : bottom(b), top(t), radius(r)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Cylinder::Cylinder(const Point3& b, const Point3& t, double r, shared_texture s)
    : Object(s), bottom(b), top(t), radius(r)
{}

Cylinder::Cylinder(const Point3& b, const Point3& t, double r, const Color& c)
    : Object(std::make_shared<Unique>(c)), bottom(b), top(t), radius(r)
{}

Vect Cylinder::get_normal_at(const Vect& point) const {
    return normal;
    //return Vect(point.x - center.x, 0, point.z - center.z).normalize();
}

bool Cylinder::find_intersection(const Ray& ray, double& t_min, double& t_max) {
    Vect m = (this->bottom + this->top) / 2;
    Vect pos = ray.origin - m;

    Vect n = (bottom - top)/2;
    float l = n.magnitude();
    n = n / l;


    // intersect infinite cylinder
    // flatten everything along the axis
    Vect r = (ray.direction - n * vector::dot(ray.direction, n));
    float rl = r.magnitude();
    r = r / rl;
    Vect p = pos - n * vector::dot(pos, n);
    float rdp = vector::dot(r,p);
    float pp = p.square_length();
    float q = pp - rdp*rdp;
    if ( q >= radius*radius ) return false;

    float d = sqrt(radius*radius-q);
    float front = (-rdp - d)/rl;
    float back = (-rdp + d)/rl;
    normal = (p+r * front * rl).normalize();

    // intersect facing plane
    float rdn = vector::dot(ray.direction,n);
    float pdn = vector::dot(pos,n);

    if( rdn < 0 ) { n = n * -1; rdn = rdn * -1; pdn = pdn * -1; }

    float front2 = (-l-pdn)/rdn;

    if ( front2 > front )
    {
        front = front2;
        normal = n * -1;
    }


    // clip the back sides
    if (
            front > back || // clip to back of cylinder
            pdn+rdn*front > l // clip to back plane
       )
        return false;

    if (front <= t_min || front >= t_max) return false;

    t_max = front;
    return true;
}

int Cylinder::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
