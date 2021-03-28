#pragma once

#include "texture_material.hh"
#include "noise.hh"

enum PerlinNoiseType : int {
    NOISE,
    TURBULENCE
};

class PerlinNoise : public TextureMaterial {
public:
    PerlinNoise();
    PerlinNoise(double s);

    virtual Color get_color(const Point3&, double, double) const override;

    /* Attributes */
    Noise noise;
    double scale;
    PerlinNoiseType type;
};
