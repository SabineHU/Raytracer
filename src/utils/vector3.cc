#include <cmath>

#include "vector3.hh"

Vect::Vect()
    : x(0), y(0), z(0)
{}

Vect::Vect(double a, double b, double c)
    : x(a), y(b), z(c)
{}

double Vect::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vect Vect::normalize() const {
    return Vect(x, y, z) / magnitude();
}

Vect Vect::negative() const {
    return Vect(-x, -y, -z);
}

Vect Vect::operator+(const Vect& u) const {
    return Vect(x + u.x, y + u.y, z + u.z);
}
Vect Vect::operator-(const Vect& u) const {
    return Vect(x - u.x, y - u.y, z - u.z);
}
Vect Vect::operator*(const Vect& u) const {
    return Vect(x * u.x, y * u.y, z * u.z);
}
Vect Vect::operator/(const Vect& u) const {
    return Vect(x / u.x, y / u.y, z / u.z);
}

Vect Vect::operator+(double u) const {
    return Vect(x + u, y + u, z + u);
}
Vect Vect::operator-(double u) const {
    return Vect(x - u, y - u, z - u);
}
Vect Vect::operator*(double u) const {
    return Vect(x * u, y * u, z * u);
}
Vect Vect::operator/(double u) const {
    return Vect(x / u, y / u, z / u);
}

static double clamp_value(double value) {
    if (value < 0)
        return 0;
    return value > 1 ? 1 : value;
}

Vect Vect::clamp() const {
    double xx = x;
    double yy = y;
    double zz = z;

    double sum = x + y + z;
    if (sum > 3) {
        xx = x + (sum - 3) * (x / sum);
        yy = y + (sum - 3) * (y / sum);
        zz = z + (sum - 3) * (z / sum);
    }

    return Vect(clamp_value(xx), clamp_value(yy), clamp_value(zz));
}
