#ifndef _SPHERE_H
#define _SPHERE_H

#include "math.hh"
#include "Object.h"
#include "vector3.hh"

class Sphere : public Object {
    Vect center;
    double radius;
    Color color;

    public:

    Sphere ();

    Sphere (Vect, double, Color);

    // method functions
    Vect getSphereCenter () { return center; }
    double getSphereRadius () { return radius; }
    virtual Color getColor () { return color; }

    virtual Vect getNormalAt(Vect point) {
        // normal always points away from the center of a sphere
        return (point - center).normalize();
    }

    virtual double findIntersection(Ray ray) {
        auto oc = ray.getRayOrigin() - this->center;

        double a = 1; // normalized
        double b = 2 * oc.dotProduct(ray.getRayDirection());
        double c = oc.dotProduct(oc) - this->radius * this->radius;

        double discriminant = b * b - 4 * a * c;

        if (discriminant <= 0)
            return -1;

        double x1 = math::quadratic_equation_root_1(a, b, discriminant) - 0.000001;
        if (x1 > 0)
            return x1;
        return math::quadratic_equation_root_2(a, b, discriminant) - 0.000001;
    }

};

Sphere::Sphere () {
    center = Vect(0,0,0);
    radius = 1.0;
    color = Color(0.5,0.5,0.5, 0);
}

Sphere::Sphere (Vect centerValue, double radiusValue, Color colorValue) {
    center = centerValue;
    radius = radiusValue;
    color = colorValue;
}

#endif
