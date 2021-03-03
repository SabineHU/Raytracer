#pragma once

#include "vector3.hh"

class Ray {
public:
    Ray();

    Ray(Vect, Vect);

    Vect getRayOrigin () { return origin; }
    Vect getRayDirection () { return direction; }

    Vect origin;
    Vect direction;

};

