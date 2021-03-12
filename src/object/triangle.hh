#pragma once

#include "object.hh"

class Triangle : public Object {
public:
    Triangle();
    Triangle(const Point3&, const Point3&, const Point3&);
    Triangle(const Point3&, const Point3&, const Point3&, shared_texture);
    Triangle(const Point3&, const Point3&, const Point3&, const Color&);

    /* Methods */
    virtual Vect get_normal_at(const Vect& point) const override;
    virtual double find_intersection(const Ray& ray) const override;

    virtual int get_isolevel_at(const Point3&) const override;

private:
    Vect get_normal() const;
    double get_distance() const;

    /* Attributes */
    Point3 A;
    Point3 B;
    Point3 C;
};
