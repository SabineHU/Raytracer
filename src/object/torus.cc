#include "torus.hh"
#include "lambertian.hh"
#include "vector3_op.hh"
#include "math.hh"

Torus::Torus()
    : Object(), position(Vect())
{}

Torus::Torus(const Point3& p)
    : Object(), position(p)
{}

Vect Torus::get_normal(const Point3& point) const {
    auto x = Vect(1, 1, -1) * position.x * position.x;
    auto y = point.square_length() - position.y * position.y;

    return point * (x * -1 + y);
}

static double get_double_inv_condition(double x, double r, double k, bool sgn) {
    double t = x - r - k;

    return sgn ? t : 2 / t;
}

static double get_min_quartic_roots(double d1, double h1, double h2, double k3, double t_min, bool positive) {
    double t1 = get_double_inv_condition(-d1,  h1, k3, positive);
    double t2 = get_double_inv_condition(-d1, -h1, k3, positive);
    double t3 = get_double_inv_condition( d1,  h2, k3, positive);
    double t4 = get_double_inv_condition( d1, -h2, k3, positive);

    double t = t1 > t_min ? t_min : t1;
    t = t2 > t ? t : t2;
    t = t3 > t ? t : t3;

    return t4 > t ? t : t4;
}

static double get_min_quadratic_roots(double x, double r, double k3, bool s) {
    double t1 = get_double_inv_condition(x, r, k3, s);
    double t2 = get_double_inv_condition(-x, r, k3, s);

    return t1 > t2 ? t2 : t1;
}

static void init_kn(double& k0, double& k1, double& k2, double& k3, bool& positive, const Point3& position, const Ray& ray) {
    double Ra2 = position.dot_x();
    double n = vector::dot(ray.origin,ray.direction);
    double k = (ray.origin.square_length() + Ra2 - position.dot_y()) / 2.0;

    k3 = n;
    k2 = n * n - Ra2 * (vector::dot_xy(ray.direction, ray.direction)) + k;
    k1 = n * k - Ra2 * (vector::dot_xy(ray.direction, ray.origin));
    k0 = k * k - Ra2 * (vector::dot_xy(ray.origin, ray.origin));

    if (std::abs(k3 * (k3 * k3 - k2) + k1) < 0.01)
    {
        positive = false;
        std::swap(k1, k3);
        k0 = 1 / k0;
        k1 *= k0;
        k2 *= k0;
        k3 *= k0;
    }
}

static void init_cn(double& c0, double& c1, double& c2, double k0, double k1, double k2, double k3) {
    c2 = 2 * k2 - 3 * k3 * k3;
    c1 = (k3 * (k3 * k3 - k2) + k1) * 2;
    c0 = (k3 * (k3 * (c2 + 2 * k2) - 8 * k1) + 4 * k0) / 3;

    c2 /= 3;
}

static void init_xr(double& x, double& r, double c1, double c2, double R, double delta) {
    delta = sqrt(delta);
    double v = math::cube_root(R + delta);
    double u = math::cube_root(R - delta);

    Vect s(v + u + 4 * c2, (v - u) * std::sqrt(3), 0);
    double y = std::sqrt((s.magnitude() + s.x) / 2);

    x = s.y / (2 * y);
    r = 2 * c1 / (x * x + y * y);
}

bool Torus::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    bool positive = true;

    double k0, k1, k2, k3;
    init_kn(k0, k1, k2, k3, positive, this->position, ray);

    double c0, c1, c2;
    init_cn(c0, c1, c2, k0, k1, k2, k3);

    double Q = c2 * c2 + c0;
    double R = c2 * c2 * c2 - 3 * c2 * c0 + c1 * c1;
    double delta = R * R - Q * Q * Q;

    if (delta >= 0) {
        init_xr(k0, k1, c1, c2, R, delta);
        c0 = get_min_quadratic_roots(k0, k1, k3, positive);
    } else {
        Q = std::sqrt(Q);
        c0 = Q * cos(acos(-R / (Q * Q * Q)) / 3.0);
        delta = -c0 - c2;

        if (delta < 0) return false;
        delta = std::sqrt(delta);

        k0 = std::sqrt(c0 - 2 * c2 + c1 / delta);
        k1 = std::sqrt(c0 - 2 * c2 - c1 / delta);

        c0 = get_min_quartic_roots(delta, k0, k1, k3, t_min, positive);
    }

    if (c0 <= t_min || c0 >= t_max) return false;
    t_max = c0;
    info.point = ray.origin + ray.direction * t_max;
    info.normal = this->get_normal(info.point);
    this->get_properties(info);

    return true;
}
