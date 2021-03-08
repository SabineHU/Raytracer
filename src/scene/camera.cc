#include "camera.hh"
#include "vector3_op.hh"

Camera::Camera() {
    campos = Vect(0,0,0);
    camdir = Vect(0,0,1);
    camright = Vect(0,0,0);
    camdown = Vect(0,0,0);
}

Camera::Camera(const Vect& look_from, const Vect& look_at, const Vect& vup)
{
    this->campos = look_from;
    this->camdir = (look_at - look_from).normalize();
    this->camright = vector::cross(vup, camdir).normalize();
    this->camdown = vector::cross(camright, camdir);
}

Ray Camera::get_ray(double x, double y) const {
    return Ray(campos, get_ray_direction(x, y));
}

Vect Camera::get_ray_direction(double x, double y) const {
    return (camdir + camright * (x - 0.5) + camdown * (y - 0.5)).normalize();
}

