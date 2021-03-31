#pragma once

#include "texture_material.hh"
#include "noise.hh"

class PerlinNoise : public TextureMaterial {
public:
    PerlinNoise();
    PerlinNoise(double s);
    PerlinNoise(double s, PerlinNoiseType t);
    PerlinNoise(double s, PerlinNoiseType t, const Color& c1, const Color& c2);

    virtual Color get_color(const Point3&, double, double) const override;

private:
    /* Attributes */
    Noise noise;
    double scale;
    PerlinNoiseType type;

    Color color1;
    Color color2;
};
