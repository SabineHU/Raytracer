#pragma once

#include "object.hh"

class IntersectionInfo {
public:
    Point3 point;
    shared_object object;
    double distance;
    Vect normal;
    Color color;

    Vect barycenter;
};
