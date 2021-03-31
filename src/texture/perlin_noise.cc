#include "perlin_noise.hh"

PerlinNoise::PerlinNoise()
    : TextureMaterial(), scale(1), noise(Noise(NOISE)),
    color1(Color(0, 0, 0)), color2(Color(1, 1, 1))
{}

PerlinNoise::PerlinNoise(double s)
    : TextureMaterial(), scale(s), noise(Noise(NOISE)),
    color1(Color(0, 0, 0)), color2(Color(1, 1, 1))
{}

PerlinNoise::PerlinNoise(double s, PerlinNoiseType t)
    : TextureMaterial(), scale(s), noise(Noise(t))
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
    : TextureMaterial(), scale(s), noise(t), color1(c1), color2(c2)
{}

Color PerlinNoise::get_color(const Point3& p, double, double) const {
    double t = this->noise.compute(p, scale);
    return color1 * t + color2 * (1 - t);
}
