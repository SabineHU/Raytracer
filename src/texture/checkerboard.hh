#pragma once

#include "texture_material.hh"

class CheckerBoard : public TextureMaterial {
public:
    CheckerBoard();
    CheckerBoard(const Color&, const Color&);
    CheckerBoard(const Color&, const Color&, double);

    virtual Color get_color(const Ray&, const Vect&) const override;

private:
    Color color1;
    Color color2;
};
