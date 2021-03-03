#include <iostream>

#include "image.hh"

namespace image {

Image::Image(int w, int h)
    : width(w), height(h)
{
    pixels = new Point3*[width];
    for (int i = 0; i < width; ++i)
        pixels[i] = new Point3[height];
}

Image::~Image() {
    for (int i = 0; i < width; ++i)
        delete [] pixels[i];
    delete [] pixels;
}

double Image::get_ratio() const {
    return (double) width / (double) height;
}

void Image::save() const {
    std::cout << "P3" << std::endl;
    std::cout << width << ' ' << height << std::endl;
    std::cout << "255" << std::endl;

    for (int j = this->height - 1; j >= 0; --j) {
        for (int i = 0; i < this->width; ++i) {
            std::cout << (int) (pixels[i][j].x * 255) << ' ';
            std::cout << (int) (pixels[i][j].y * 255) << ' ';
            std::cout << (int) (pixels[i][j].z * 255) << std::endl;
        }
    }
}
}
