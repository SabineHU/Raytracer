#pragma once

#include "vector3.hh"

class Camera {
public:

    Camera();
    Camera(Vect, Vect, Vect, Vect);

    Vect getCameraPosition () { return campos; }
    Vect getCameraDirection () { return camdir; }
    Vect getCameraRight () { return camright; }
    Vect getCameraDown () { return camdown; }

    /* Attributes */
    Vect campos;
    Vect camdir;
    Vect camright;
    Vect camdown;

};
