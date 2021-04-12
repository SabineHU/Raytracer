#include <cmath>

#include "noise.hh"
#include "random.hh"
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

static double lerp(double i, double x) {
    return i * x + (1 - i) * (1 - x);
}

static double interpolate(Vect c[2][2][2], double x, double y, double z) {
    double xx = smooth_step(x);
    double yy = smooth_step(y);
    double zz = smooth_step(z);

    double res = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {

                Vect factor(x - i, y - j, z - k);
                res += lerp(i, xx) * lerp(j, yy) * lerp(k, zz) * vector::dot(c[i][j][k], factor);
            }
        }
    }
    return res;
}

double Noise::compute(const Point3& p, int depth) const {
    switch (type) {
    case CLOUD:
        return this->cloud(p * scale) * 0.7;
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

double Noise::compute(double x, double y, double z) const {
    return 0.5 + this->noise(Point3(x, y, z) * scale) * 0.5;
}

double Noise::noise(const Point3& point) const {
    int x = std::floor(point.x);
    int y = std::floor(point.y);
    int z = std::floor(point.z);

    Vect c[2][2][2] = {};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                int index = this->permutation[(x + i) & mask]
                    & this->permutation[((y + j) & mask) * 2]
                    ^ this->permutation[((z + k) & mask) * 3];
                c[i][j][k] = this->random_vect[index];
            }
        }
    }
    return interpolate(c, point.x - x, point.y - y, point.z - z);
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

double Noise::cloud(const Point3& p, int depth) const {
    double res = 0;
    double factor = 1;
    double freq = 1;
    for (int i = 0; i < depth; i++) {
        res += this->noise(p * freq) * factor;
        factor *= 0.5;
        freq *= 2;
    }
    return res;
}
