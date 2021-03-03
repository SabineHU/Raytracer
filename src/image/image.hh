#pragma once

#include "vector3.hh"

namespace image {

class Image {
public:
    Image() = delete;
    Image(int w, int h);

    ~Image();

    double get_ratio() const;
    void save() const;

    /* Attributes */
    int width;
    int height;

    Vect **pixels;
};

}
