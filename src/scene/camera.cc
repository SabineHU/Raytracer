#include "camera.hh"

Camera::Camera () {
    campos = Vect(0,0,0);
    camdir = Vect(0,0,1);
    camright = Vect(0,0,0);
    camdown = Vect(0,0,0);
}

Camera::Camera (const Vect& pos, const Vect& dir, const Vect& right,
        const Vect& down)
    : campos(pos), camdir(dir), camright(right), camdown(down)
{}

Ray Camera::get_ray(double x, double y) const {
    return Ray(campos, get_ray_direction(x, y));

}

Vect Camera::get_ray_direction(double x, double y) const {
    return (camdir + camright * (x - 0.5) + camdown * (y - 0.5)).normalize();
}

