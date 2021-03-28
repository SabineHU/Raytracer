#pragma once

#include "vector3.hh"

static const int count = 256;

class Noise {
public:
    Noise();

    double noise(const Point3&) const;
    double turb(const Point3&, int depth=7) const;

private:
    /* Attributes */
    Vect ranvec[count];
    int perm_x[count];
    int perm_y[count];
    int perm_z[count];
};
