#pragma once

#include "texture_material.hh"

class Strip : public TextureMaterial {
public:
    Strip();
    Strip(const Color&, const Color&);
    Strip(const Color&, const Color&, bool, double);
    Strip(const Color&, const Color&, bool, double, double, double);

    virtual Color get_color(const Point3&, double, double) const override;

private:
    Color color1;
    Color color2;

    bool horizontal;
    double scale;
};
