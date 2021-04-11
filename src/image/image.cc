#include <iostream>
#include <cmath>

#include "image.hh"
#include "file.hh"

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

void Image::save(const std::string& filename) const {
    std::ofstream file = file::open_writing_file(filename);

    file << "P3" << std::endl;
    file << width << ' ' << height << std::endl;
    file << "255" << std::endl;

    for (int j = this->height - 1; j >= 0; --j) {
        for (int i = 0; i < this->width; ++i) {
            auto pixel = pixels[i][j].clamp();
            file << (int) (pixel.x * 255) << ' ';
            file << (int) (pixel.y * 255) << ' ';
            file << (int) (pixel.z * 255) << std::endl;
        }
    }

    std::cerr << "Saved at " << filename << std::endl;
    file.close();
}

}
