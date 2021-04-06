#pragma once

#include <vector>

#include "texture_material.hh"

class ImageTexture : public TextureMaterial {
public:
    ImageTexture() = default;
    ImageTexture(const char* filename);

    virtual Color get_color(const Point3&, double, double) const override;

private:
    void parse_file(const char* filename);

    /* Attributes */
    int width;
    int height;

    std::vector<double> pixels;

    std::vector<double> red;
    std::vector<double> green;
    std::vector<double> blue;
};
