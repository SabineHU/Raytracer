#pragma once

#include "texture_material.hh"

class ImageTexture : public TextureMaterial {
public:
    ImageTexture() = delete;
    ImageTexture(const char* filename);

    virtual Color get_color(const Point3&, double, double) const override;
};
