#include "rotate.hh"
#include "math.hh"
#include "vector3_op.hh"

RotatedObject::RotatedObject(shared_object o, double deg, Axis a)
: Object(), obj(o), axis(a)
{
    auto theta = math::degree_to_radian(deg);
    this->sin = std::sin(theta);
    this->cos = std::cos(theta);
}

Vect RotatedObject::get_normal_at(const Point3& point, double u, double v) const {
    auto normal = this->obj->get_normal_at(point, u, v);
    // Rotation of -theta
    // sin(-theta) = -sin(theta)
    // cos(-theta) =  cos(theta)
    switch (axis) {
    case AXIS_X:
        return vector::rotate_x(normal, -sin, cos);
    case AXIS_Y:
        return vector::rotate_y(normal, -sin, cos);
    default:
        return vector::rotate_z(normal, -sin, cos);
    }
}

bool RotatedObject::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    Point3 orig, dir;
    /* Rotate ray */
    switch (axis) {
    case AXIS_X:
        orig = vector::rotate_x(ray.origin, sin, cos);
        dir = vector::rotate_x(ray.direction, sin, cos);
        break;
    case AXIS_Y:
        orig = vector::rotate_y(ray.origin, sin, cos);
        dir = vector::rotate_y(ray.direction, sin, cos);
        break;
    default:
        orig = vector::rotate_z(ray.origin, sin, cos);
        dir = vector::rotate_z(ray.direction, sin, cos);
        break;
    }

    if (!this->obj->find_intersection(Ray(orig, dir), t_min, t_max, info))
        return false;

    switch (axis) {
    case AXIS_X:
        info.point = vector::rotate_x(info.point, -sin, cos);
        break;
    case AXIS_Y:
        info.point = vector::rotate_y(info.point, -sin, cos);
        break;
    default:
        info.point = vector::rotate_z(info.point, -sin, cos);
        break;
    }
    return true;
}

int RotatedObject::get_isolevel_at(const Point3&) const {
    // TODO: isolevel
    return 100;
}
