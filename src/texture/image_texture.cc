#include <fstream>
#include <cstdlib>
#include <iostream>

#include "image_texture.hh"
#include "math.hh"

ImageTexture::ImageTexture(const std::string& filename)
    : TextureMaterial()
{
    parse_file(filename);
}

void ImageTexture::parse_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file " << filename << std::endl;
        exit(1);
    }

    /* Parse header */
    std::string line;
    getline(file, line); // P3
    getline(file, line); // comment
    getline(file, line); // size

    size_t dist;
    this->width = std::stoi(line, &dist);
    this->height = std::stoi(line.substr(dist));

    getline(file, line); // max value

    for (std::string line; getline(file, line);) {
        if (line[0] == '#') continue;
        this->red.push_back(std::stoi(line));

        getline(file, line);
        this->green.push_back(std::stoi(line));

        getline(file, line);
        this->blue.push_back(std::stoi(line));
    }

    file.close();
}

Color ImageTexture::get_color(const Point3&, double u, double v) const {
    if (u < 0) u = std::fmod(u, width - 1) + width - 1;
    if (v < 0) v = std::fmod(v, height - 1) + height - 1;

    int x = std::round(u * (width - 1));
    int y = std::round(v * (height - 1));
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= width) x %= width - 1;
    if (y >= height) y %= height - 1;

    int index = math::round_multiple(y * width + x, 3);

    double r = this->red[index] / 255.0;
    double g = this->green[index] / 255.0;
    double b = this->blue[index] / 255.0;

    return Color(r, g, b);

}
