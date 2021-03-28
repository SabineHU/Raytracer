#include "perlin_noise.hh"

PerlinNoise::PerlinNoise()
    : TextureMaterial(), scale(1), type(NOISE)
{}

PerlinNoise::PerlinNoise(double s)
    : TextureMaterial(), scale(s), type(WOOD)
{}

Color PerlinNoise::get_color(const Point3& p, double, double) const {
    if (type == NOISE)
        return Color(1, 1, 1) * 0.5 * (1 + this->noise.noise(p * scale));

    if (type == TURBULENCE)
        return Color(1, 1, 1) * 0.5 * (1 + sin(scale*p.z + noise.turb(p) * 10));

    if (type == MARBLE)
        return Color(1, 1, 1) * 0.5 * (1 + sin(scale*p.z + noise.marble(p) * 10));

    auto t = sin(scale*p.z + noise.wood(p) * 10);
    return Color(0.3, 0.15, 0) * t + Color(0.6, 0.3, 0) * (1 - t);
    //return Color(1, 1, 1) * noise.turb(p * scale);
    //return Color(1, 1, 1) * noise.turb(p * scale);
    //return Color(1, 1, 1) * 0.5 * (1 + this->noise.noise(p * scale));
}
