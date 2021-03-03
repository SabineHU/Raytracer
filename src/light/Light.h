#ifndef _Light_H
#define _Light_H

#include "Source.h"
#include "vector3.hh"

class Light : public Source {
public:

    Light ();

    Light (Vect, Color);

    // method functions
    virtual Vect getLightPosition () { return position; }
    virtual Color getLightColor () { return color; }

    Vect position;
    Color color;
};

Light::Light () {
    position = Vect(0,0,0);
    color = Color(1,1,1, 0);
}

Light::Light (Vect p, Color c) {
    position = p;
    color = c;
}

#endif
