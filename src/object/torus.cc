#include "torus.hh"
#include "unique.hh"
#include "vector3_op.hh"
#include "math.hh"

Torus::Torus()
    : position(Vect())
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Torus::Torus(const Point3& p)
    : position(p)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Torus::Torus(const Point3& p, shared_texture t)
    : Object(t), position(p)
{}

Torus::Torus(const Point3& p, const Color& c)
    : Object(std::make_shared<Unique>(c)), position(p)
{}

Vect Torus::get_normal_at(const Vect& point) const {
    auto x = Vect(1, 1, -1) * position.x * position.x;
    auto y = point.square_length() - position.y * position.y;
    return (point * (x * -1 + y)).normalize();
}

static double get_double_inv_condition(double x, double r, double k, bool sgn) {
    double t = x - r - k;
    if (sgn)
        return t;
    return 2 / t;
}

static double get_min_quadratic_roots(double d1, double h1, double h2,
        double k3, double t_min, bool positive) {
    double t1 = get_double_inv_condition(-d1,  h1, k3, positive);
    double t2 = get_double_inv_condition(-d1, -h1, k3, positive);
    double t3 = get_double_inv_condition( d1,  h2, k3, positive);
    double t4 = get_double_inv_condition( d1, -h2, k3, positive);

    double t = t1 > t_min ? t_min : t1;
    t = t2 > t ? t : t2;
    t = t3 > t ? t : t3;
    return t4 > t ? t : t4;
}

bool Torus::find_intersection(const Ray& ray, double& t_min, double& t_max) {
    bool positive = true;
    double Ra2 = position.dot_x();
    double n = vector::dot(ray.origin,ray.direction);
    double k = (ray.origin.square_length() + Ra2 - position.dot_y()) / 2.0;
    double k3 = n;
    double k2 = n*n - Ra2*(vector::dot_xy(ray.direction, ray.direction)) + k;
    double k1 = n*k - Ra2*(vector::dot_xy(ray.direction, ray.origin));
    double k0 = k*k - Ra2*(vector::dot_xy(ray.origin, ray.origin));

    if (std::abs(k3 * (k3 * k3 - k2) + k1) < 0.01)
    {
        positive = false;
        std::swap(k1, k3);
        k0 = 1 / k0;
        k1 = k1 * k0;
        k2 = k2 * k0;
        k3 = k3 * k0;
    }

    double c2 = k2 * 2.0 - 3.0 * k3 * k3;
    double c1 = k3 * (k3 * k3 - k2) + k1;
    double c0 = k3 * (k3 * (c2 + 2.0 * k2) - 8.0 * k1) + 4.0 * k0;
    c2 /= 3.0;
    c1 *= 2.0;
    c0 /= 3.0;
    double Q = c2 * c2 + c0;
    double R = c2 * c2 * c2 - 3.0 * c2 * c0 + c1 * c1;
    double delta = R * R - Q * Q * Q;

    if (delta >= 0)
    {
        delta = sqrt(delta);
        double v = math::cube_root(R + delta);
        double u = math::cube_root(R - delta);
        Vect s(v + u + c2 * 4, (v - u) * std::sqrt(3), 0);
        double y = std::sqrt((s.magnitude() + s.x) / 2);
        double x = s.y / (2 * y);
        double r = 2 * c1 / (x * x + y * y);

        double t1 = get_double_inv_condition(x, r, k3, positive);
        double t2 = get_double_inv_condition(-x, r, k3, positive);

        double t = t1 > t2 ? t2 : t1;
        if (t <= t_min ||  t >= t_max)
            return false;
        t_max = t;
        return true;
    }

    double sQ = std::sqrt(Q);
    double w = sQ * cos(acos(-R / (sQ * Q)) / 3.0);
    double d2 = -(w + c2);
    if (d2 < 0) return false;
    double d1 = sqrt(d2);
    double h1 = sqrt(w - 2 * c2 + c1 / d1);
    double h2 = sqrt(w - 2 * c2 - c1 / d1);

    double t = get_min_quadratic_roots(d1, h1, h2, k3, t_min, positive);
    if (t <= t_min || t >= t_max)
        return false;

    t_max = t;
    return true;
}

int Torus::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
