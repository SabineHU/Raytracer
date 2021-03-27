#include "strip.hh"

Strip::Strip()
    : TextureMaterial(), color1(Color(0, 0, 0)), color2(Color(1, 1, 1)),
    horizontal(true), scale(15)
{}

Strip::Strip(const Color& c1, const Color& c2)
    : TextureMaterial(), color1(c1), color2(c2), horizontal(true), scale(15)
{}

Strip::Strip(const Color& c1, const Color& c2, bool h, double s)
    : TextureMaterial(), color1(c1), color2(c2), horizontal(h), scale(s)
{}

Strip::Strip(const Color& c1, const Color& c2, bool h, double s,
        double kd, double ks)
    : TextureMaterial(kd, ks), color1(c1), color2(c2), horizontal(h), scale(s)
{}

Color Strip::get_color(const Point3&, double u, double v) const {
    int x = (int) std::floor(u * scale);
    if (horizontal) {
        return x % 2 == 0 ? color1 : color2;
    }

    int y = (int) std::floor(v * scale);
    return y % 2 == 0 ? color1 : color2;
}
