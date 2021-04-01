#include "noise.hh"
#include "random_color.hh"
#include "vector3_op.hh"

Noise::Noise()
    : type(NOISE), scale(1)
{
    this->init_noise_arrays();
}

Noise::Noise(PerlinNoiseType t)
    : type(t), scale(1)
{
    this->init_noise_arrays();
}

Noise::Noise(PerlinNoiseType t, double s)
    : type(t), scale(s)
{
    this->init_noise_arrays();
}

void Noise::init_noise_arrays() {
    for (int i = 0; i < count; ++i)
        random_vect[i] = r_random::random_vector(-1, 1).normalize();

    for (int i = 0; i < count * 3; ++i) {
        permutation[i] = i / 3;
    }

    r_random::shuffle(permutation, count * 3);
}


static double smooth_step(double x) {
    if (x <= 0) return 0;
    if (x >= 1) return 1;
    return x * x * (3 - 2 * x);
}

static double f(double i, double x) {
    return i * x + (1 - i) * (1 - x);
}

static double interpolate(Vect c[2][2][2], const Vect& point) {
    double u = point.x - std::floor(point.x);
    double v = point.y - std::floor(point.y);
    double w = point.z - std::floor(point.z);

    double uu = smooth_step(u);
    double vv = smooth_step(v);
    double ww = smooth_step(w);

    double res = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {

                Vect factor(u - i, v - j, w - k);
                res += f(i, uu) * f(j, vv) * f(k, ww) * vector::dot(c[i][j][k], factor);
            }
        }
    }
    return res;
}

double Noise::compute(const Point3& p, int depth) const {
    switch (type) {
    case NOISE:
        return 0.5 + this->noise(p * scale) * 0.5;
    case TURBULENCE:
        return 0.5 + sin(scale * p.z + this->turb(p, depth) * 10) * 0.5;
    case MARBLE:
        return 1 - sqrt(abs(sin(scale * p.z + this->marble(p, depth) * 2 * M_PI)));
    default: // WOOD
        return sin(scale * p.z + this->wood(p) * 10);
    }
}

double Noise::noise(const Point3& point) const {
    int x = std::floor(point.x);
    int y = std::floor(point.y);
    int z = std::floor(point.z);

    Vect c[2][2][2] = {};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++)
                c[i][j][k] = this->random_vect[
                        this->permutation[(x + i) & mask] ^
                        this->permutation[((y + j) & mask) * 2] ^
                        this->permutation[((z + k) & mask) * 3]
                ];
        }
    }
    return interpolate(c, point);
}

double Noise::turb(const Point3& p, int depth) const {
    double res = 0;
    double factor = 1;
    Point3 tmp = p;

    for (int i = 0; i < depth; i++) {
        res += this->noise(tmp) * factor;
        factor *= 0.5;
        tmp *= 2;
    }
    return std::fabs(res);
}

double Noise::marble(const Point3& p, int depth) const {
    double res = 0;
    double factor = 1;
    Point3 tmp = p;

    for (int i = 0; i < depth; i++) {
        res += std::fabs(2 * this->noise(tmp) - 1) * factor;
        factor *= 0.5;
        tmp *= 2;
    }
    return std::fabs(res);
}

double Noise::wood(const Point3& p) const {
    return std::fabs(this->noise(p)) * 10;
}
