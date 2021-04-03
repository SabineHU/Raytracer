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
    virtual Vect get_normal_at(const Point3& point, double u, double v) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

    virtual int get_isolevel_at(const Point3&) const override;

private:
    shared_object obj;
    Axis axis;

    double sin;
    double cos;
};
