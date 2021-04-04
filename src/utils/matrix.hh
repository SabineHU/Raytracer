#pragma once

namespace matrix {

inline double determinant(const Vect& u, const Vect& v, const Vect& w){
    double res = 0;

    res = res + u.x * (v.y * w.z - w.y * v.z);
    res = res - u.y * (v.x * w.y - w.x * v.y);
    res = res + u.z * (v.z * w.y - w.x * v.y);

    return res;
}

}
