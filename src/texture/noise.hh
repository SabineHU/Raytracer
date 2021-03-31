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
    double compute(PerlinNoiseType type, const Point3& p, double scale,
        int depth=7) const;

private:
    double noise(const Point3&) const;
    double turb(const Point3&, int depth=7) const;
    double marble(const Point3&, int depth=7) const;
    double wood(const Point3&) const;

    /* Attributes */
    Vect random_vect[count];
    int permutation[count * 3];
    int perm_x[count];
    int perm_y[count];
    int perm_z[count];
};
