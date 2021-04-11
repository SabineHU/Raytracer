#pragma once

#include "object.hh"

class Triangle : public Object {
public:
    Triangle();
    Triangle(const Point3&, const Point3&, const Point3&);
    Triangle(const Point3&, const Point3&, const Point3&, const Vect&);

    /* Methods */
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const override;

protected:
    Vect get_normal() const;

public:
    /* Attributes */
    Point3 A;
    Point3 B;
    Point3 C;

    Vect normal;
};
