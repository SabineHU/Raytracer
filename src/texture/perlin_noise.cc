#include "perlin_noise.hh"

PerlinNoise::PerlinNoise()
    : TextureMaterial(), noise(Noise(NOISE)),
    color1(Color(0, 0, 0)), color2(Color(1, 1, 1))
{}

PerlinNoise::PerlinNoise(double scale)
    : TextureMaterial(), noise(Noise(NOISE, scale)),
    color1(Color(0, 0, 0)), color2(Color(1, 1, 1))
{}

PerlinNoise::PerlinNoise(double scale, PerlinNoiseType t)
    : TextureMaterial(), noise(Noise(t, scale))
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
    : TextureMaterial(), noise(t, s), color1(c1), color2(c2)
{}

Color PerlinNoise::get_color(const Point3& p, double, double) const {
    double t = this->noise.compute(p);
    if (this->noise.get_type() == CLOUD) {
        double dist = p.y + t + 0.2;
        if (dist < 0) {
            dist = std::max(0.0, std::min(-dist, 1.0));
            Color cloud = Vect(1, 1, 1) - dist * .7;
            return Vect(0.1, 0.6, 1) * dist * .4 + cloud * (1 - dist * .4);
        }
    }
    return color1 * t + color2 * (1 - t);
}
