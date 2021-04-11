#pragma once

#include "object.hh"

class Triangle : public Object {
public:
    Triangle();
    Triangle(const Point3&, const Point3&, const Point3&);
    Triangle(const Point3&, const Point3&, const Point3&, const Vect&);

    /* Methods */
    virtual Vect get_normal_at(const Point3& point, double u, double v) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

protected:
    Vect get_normal() const;
    double get_distance() const;

public:
    /* Attributes */
    Point3 A;
    Point3 B;
    Point3 C;

    Vect normal;
};
