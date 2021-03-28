#include "perlin_noise.hh"

PerlinNoise::PerlinNoise()
    : TextureMaterial(), scale(1), type(NOISE),
    color1(Color(0, 0, 0)), color2(Color(1, 1, 1))
{}

PerlinNoise::PerlinNoise(double s)
    : TextureMaterial(), scale(s), type(NOISE),
    color1(Color(0, 0, 0)), color2(Color(1, 1, 1))
{}

PerlinNoise::PerlinNoise(double s, PerlinNoiseType t)
    : TextureMaterial(), scale(s), type(t)
{
    if (t == WOOD) {
        color1 = Color(0.3, 0.15, 0);
        color2 = Color(0.6, 0.3, 0);
    } else {
        color1 = Color(0, 0, 0);
        color2 = Color(1, 1, 1);
    }
}

PerlinNoise::PerlinNoise(double s, PerlinNoiseType t,
        const Color& c1, const Color& c2)
    : TextureMaterial(), scale(s), type(t), color1(c1), color2(c2)
{}

Color PerlinNoise::get_color(const Point3& p, double, double) const {
    double t;
    switch (type) {
    case NOISE:
        t = 0.5 + this->noise.noise(p * scale) * 0.5;
        break;
    case TURBULENCE:
        t = 0.5 + sin(scale * p.z + noise.turb(p) * 10) * 0.5;
        break;
    case MARBLE:
        t = 1 - sqrt(abs(sin(scale * p.z + noise.marble(p) * 2 * M_PI)));
        break;
    default: // WOOD
        t = sin(scale * p.z + noise.wood(p) * 10);
        break;
    }

    return color1 * t + color2 * (1 - t);
}
