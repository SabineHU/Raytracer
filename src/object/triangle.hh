#pragma once

#include "object.hh"

class Triangle : public Object {
public:
    Triangle();
    Triangle(const Point3&, const Point3&, const Point3&);
    Triangle(const Point3&, const Point3&, const Point3&, shared_texture);
    Triangle(const Point3&, const Point3&, const Point3&, const Color&);

    /* Methods */
    virtual Vect get_normal_at(const Vect& point, const Point3&) const override;
    virtual double find_intersection(const Ray& ray) override;

    virtual int get_isolevel_at(const Point3&) const override;

protected:
    Vect get_normal() const;
    double get_distance() const;

public:
    /* Attributes */
    Point3 A;
    Point3 B;
    Point3 C;

    Point3 barycenter;
};
