#include "strip.hh"

Strip::Strip()
    : TextureMaterial(), color1(Color(0, 0, 0)), color2(Color(1, 1, 1)),
    horizontal(true), scale(15), planar(false)
{}

Strip::Strip(const Color& c1, const Color& c2)
    : TextureMaterial(), color1(c1), color2(c2), horizontal(true), scale(15),
    planar(false)
{}

Strip::Strip(const Color& c1, const Color& c2, bool h, double s)
    : TextureMaterial(), color1(c1), color2(c2), horizontal(h), scale(s),
    planar(false)
{}

Strip::Strip(const Color& c1, const Color& c2, bool h, double s,
        double kd, double ks)
    : TextureMaterial(kd, ks), color1(c1), color2(c2), horizontal(h), scale(s),
    planar(false)
{}

Color Strip::get_color(const Point3& p, double u, double v) const {
    double value;
    if (!planar) {
        value = horizontal ? u : v;
    } else {
        value = horizontal ? p.y : p.x;
    }
    return ((int) std::floor(value * scale)) % 2 == 0 ? color1 : color2;
}
