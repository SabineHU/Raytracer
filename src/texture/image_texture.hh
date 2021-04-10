#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "texture_material.hh"

class ImageTexture : public TextureMaterial {
public:
    ImageTexture() = default;
    ImageTexture(const std::string& filename);

    virtual Color get_color(const Point3&, double, double) const override;

    void reverse_image() {
        std::reverse(red.begin(), red.end());
        std::reverse(green.begin(), green.end());
        std::reverse(blue.begin(), blue.end());
    }

private:
    void parse_file(const std::string& filename);

    /* Attributes */
    int width;
    int height;

    std::vector<double> pixels;

    std::vector<int> red;
    std::vector<int> green;
    std::vector<int> blue;
};
