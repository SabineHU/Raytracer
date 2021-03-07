#pragma once

#include "vector3.hh"
#include "scene.hh"

namespace image {

class Image {
public:
    Image() = delete;
    Image(int w, int h);

    ~Image();

    /* Methods */
    void save() const;
    void render(const Scene&, double, int, int);

private:
    double get_ratio() const;
    void set_pixel_color(int, int, const Color&);
    void set_index_x_y(double& x, double& y, int samples, int i, int j, int k);

    /* Attributes */
public:
    int width;
    int height;

private:
    Vect **pixels;
};

}
