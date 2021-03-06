#pragma once

#include "texture_material.hh"

class CheckerBoard : public TextureMaterial {
public:
    CheckerBoard();
    CheckerBoard(const Color&, const Color&);

    virtual Color get_color(double, double, double) const;

private:
    Color color1;
    Color color2;
};
