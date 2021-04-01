#pragma once

#include "vector3.hh"

enum PerlinNoiseType {
    NOISE,
    TURBULENCE,
    MARBLE,
    WOOD
};

static const int count = 256;
static const int mask = 255;

class Noise {
public:
    Noise();
    Noise(PerlinNoiseType type);
    Noise(PerlinNoiseType type, double s);
    double compute(const Point3& p, int depth=7) const;

private:
    void init_noise_arrays();
    double noise(const Point3&) const;
    double turb(const Point3&, int depth=7) const;
    double marble(const Point3&, int depth=7) const;
    double wood(const Point3&) const;

    /* Attributes */
    PerlinNoiseType type;
    double scale;

    Vect random_vect[count];
    int permutation[count * 3];
};
