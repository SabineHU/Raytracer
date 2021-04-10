#pragma once

#include "texture_material.hh"

class CheckerBoard : public TextureMaterial {
public:
    CheckerBoard();
    CheckerBoard(const Color&, const Color&);
    CheckerBoard(shared_texture, shared_texture);

    virtual Color get_color(const Point3&, double, double) const override;

    void set_scale(double d) { scale = d; }

private:
    shared_texture color1;
    shared_texture color2;

    double scale;
};
