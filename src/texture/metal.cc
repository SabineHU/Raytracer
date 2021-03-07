#include "metal.hh"

Metal::Metal(const Color& c)
    : TextureMaterial(1), color(c)
{}

Metal::Metal(const Color& c, double s)
    : TextureMaterial(s), color(c)
{}

Color Metal::get_color(const Ray&, const Vect&) const {
    //vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    //scattered = ray(rec.p, reflected);
    //attenuation = albedo;
    //return (dot(scattered.direction(), rec.normal) > 0);
    return color;
}
