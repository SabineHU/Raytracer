#pragma once

#include "triangle.hh"

class SmoothTriangle : public Triangle {
public:
    SmoothTriangle() = default;
    SmoothTriangle(const Point3&, const Point3&, const Point3&);
    SmoothTriangle(const Point3&, const Point3&, const Point3&,
            const Vect&, const Vect&, const Vect&);

    virtual Vect get_normal_at(const Point3& point, double u, double v) const override;

    /* Attributes */
    Vect normalA;
    Vect normalB;
    Vect normalC;
};

