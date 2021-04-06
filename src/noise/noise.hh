#pragma once

#include "vector3.hh"

enum PerlinNoiseType {
    CLOUD,
    MARBLE,
    NOISE,
    RAINBOW,
    TURBULENCE,
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
    double compute(double x, double y, double z) const;

    /* Getters */
    PerlinNoiseType get_type() const { return type; }
    const int* get_permutation() const { return permutation; }

    bool operator<(const Noise& n) const {
        return this->permutation[0] < n.get_permutation()[0];
    }

private:
    void init_noise_arrays();
    double noise(const Point3&) const;
    double turb(const Point3&, int depth=7) const;
    double marble(const Point3&, int depth=7) const;
    double wood(const Point3&) const;
    double cloud(const Point3&, int depth=7) const;

    /* Attributes */
    PerlinNoiseType type;
    double scale;

    Vect random_vect[count];
    int permutation[count * 3];
};
