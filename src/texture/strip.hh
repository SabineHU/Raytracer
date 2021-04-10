#pragma once

#include "texture_material.hh"

class Strip : public TextureMaterial {
public:
    Strip() = delete;
    Strip(const Color&, const Color&);
    Strip(shared_texture, shared_texture);
    Strip(const Color&, const Color&, bool, double);
    Strip(shared_texture, shared_texture, bool, double);

    virtual Color get_color(const Point3&, double, double) const override;

    void set_horizontal(bool d) { horizontal = d; }
    void set_scale(double d) { scale = d; }
    void set_planar(bool d) { planar = d; }

private:
    shared_texture color1;
    shared_texture color2;

    bool horizontal;
    double scale;

    bool planar;
};
