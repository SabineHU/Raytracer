#pragma once

#include <string>

#include "vector3.hh"

namespace image {

class Image {
public:
    Image() = delete;
    Image(int w, int h);
    Image(double alpha, double beta, double zmin);

    ~Image();

    /* Methods */
    void set_pixel_color(int, int, const Color&);
    void save(const std::string& filename = "image.ppm") const;

    /* Getters */
    int get_width() const { return width; }
    int get_height() const { return height; }

private:
    /* Attributes */
    int width;
    int height;
    Vect **pixels;
};

}
