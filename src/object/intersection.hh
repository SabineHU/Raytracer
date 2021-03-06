#pragma once

#include "object.hh"

class IntersectionInfo {
public:
    shared_object object;
    double distance;
    Vect normal;
    Color color;
};
