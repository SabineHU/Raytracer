#pragma once

#include "object.hh"

enum Axis : int {
    AXIS_X,
    AXIS_Y,
    AXIS_Z
};

class RotatedObject : public Object {
public:
    RotatedObject() = delete;
    RotatedObject(shared_object o, double deg, Axis a);

    /* Methods */
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const override;

    virtual Color get_color_at(const Point3& point, double u, double v) const override;

private:
    Vect get_normal(const Vect& normal) const;

    /* Attributes */
    shared_object obj;
    Axis axis;

    double sin;
    double cos;
};
