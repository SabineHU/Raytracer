#include <iostream>
#include <cmath>

#include "image.hh"

namespace image {

Image::Image(int w, int h)
    : width(w), height(h)
{
    pixels = new Point3*[width];
    for (int i = 0; i < width; ++i)
        pixels[i] = new Point3[height];
}

Image::Image(double alpha, double beta, double zmin)
{
    width = 2 * zmin * std::tan(beta / 2.0);
    height = 2 * zmin * std::tan(alpha / 2.0);

    pixels = new Point3*[width];
    for (int i = 0; i < width; ++i)
        pixels[i] = new Point3[height];
}

Image::~Image() {
    for (int i = 0; i < width; ++i)
        delete [] pixels[i];
    delete [] pixels;
}

void Image::set_pixel_color(int i, int j, const Color& color) {
    this->pixels[i][j].x = color.x;
    this->pixels[i][j].y = color.y;
    this->pixels[i][j].z = color.z;
}

void Image::save() const {
    std::cout << "P3" << std::endl;
    std::cout << width << ' ' << height << std::endl;
    std::cout << "255" << std::endl;

    for (int j = this->height - 1; j >= 0; --j) {
        for (int i = 0; i < this->width; ++i) {
            auto pixel = pixels[i][j].clamp();
            std::cout << (int) (pixel.x * 255) << ' ';
            std::cout << (int) (pixel.y * 255) << ' ';
            std::cout << (int) (pixel.z * 255) << std::endl;
        }
    }
}

}
