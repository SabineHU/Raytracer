#include "perlin_noise.hh"

PerlinNoise::PerlinNoise()
    : TextureMaterial(), scale(1), type(NOISE)
{}

PerlinNoise::PerlinNoise(double s)
    : TextureMaterial(), scale(s), type(TURBULENCE)
{}

Color PerlinNoise::get_color(const Point3& p, double, double) const {
    if (type == NOISE)
        return Color(1, 1, 1) * 0.5 * (1 + this->noise.noise(p * scale));
    return Color(1,1,1) * 0.5 * (1 + sin(scale*p.z + noise.turb(p) * 10));
    //return Color(1, 1, 1) * noise.turb(p * scale);
    //return Color(1, 1, 1) * 0.5 * (1 + this->noise.noise(p * scale));
}
