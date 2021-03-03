#ifndef _Plane_H
#define _Plane_H

#include "math.h"
#include "Object.h"
#include "vector3.hh"

class Plane : public Object {

public:
    Plane ();

    Plane (Vect, double, Color);

    // method functions
    Vect getPlaneNormal () { return normal; }
    double getPlaneDistance () { return distance; }
    virtual Color getColor () { return color; }

    virtual Vect getNormalAt(Vect) {
        return normal;
    }

    virtual double findIntersection(Ray ray) {
        Vect ray_direction = ray.getRayDirection();

        double a = ray_direction.dotProduct(normal);

        if (a == 0) {
            // ray is parallel to the plane
            return -1;
        }
        else {
            double b = normal.dotProduct(ray.getRayOrigin() + normal * -distance);
            return -1*b/a;
        }
    }

    /* Attributes */
    Vect normal;
    double distance;
    Color color;

};

Plane::Plane () {
    normal = Vect(1,0,0);
    distance = 0;
    color = Color(0.5,0.5,0.5, 0);
}

Plane::Plane (Vect normalValue, double distanceValue, Color colorValue) {
    normal = normalValue;
    distance = distanceValue;
    color = colorValue;
}

#endif
