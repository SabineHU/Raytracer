#pragma once

#include "triangle.hh"

class SmoothTriangle : public Triangle {
public:
    SmoothTriangle() = default;
    SmoothTriangle(const Point3&, const Point3&, const Point3&);
    SmoothTriangle(const Point3&, const Point3&, const Point3&, const Color&);
    SmoothTriangle(const Point3&, const Point3&, const Point3&,
            const Vect&, const Vect&, const Vect&);

    virtual Vect get_normal_at(const Vect&, const Point3&) const override;

    /* Attributes */
    Vect normalA;
    Vect normalB;
    Vect normalC;
};

