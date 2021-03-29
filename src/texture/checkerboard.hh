#pragma once

#include "texture_material.hh"

class CheckerBoard : public TextureMaterial {
public:
    CheckerBoard();
    CheckerBoard(const Color&, const Color&);
    CheckerBoard(const Color&, const Color&, double, double);

    virtual Color get_color(const Point3&, double, double) const override;

    void set_scale(double d) { scale = d; }

private:
    Color color1;
    Color color2;

    double scale;
};
