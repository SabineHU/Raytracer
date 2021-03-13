#include <cmath>

#include "vector3.hh"

Vect::Vect()
    : x(0), y(0), z(0), iso(0)
{}

Vect::Vect(double a, double b, double c)
    : x(a), y(b), z(c), iso(0)
{}

Vect::Vect(double a, double b, double c, double d)
    : x(a), y(b), z(c), iso(d)
{}

double Vect::square_length() const {
    return x * x + y * y + z * z;
}

double Vect::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vect Vect::normalize() const {
    return Vect(x, y, z) / magnitude();
}

Vect Vect::negative() const {
    return Vect(-x, -y, -z);
}

double Vect::dot_x() const {
    return x * x;
}

double Vect::dot_y() const {
    return y * y;
}

double Vect::dot_z() const {
    return z * z;
}

bool Vect::is_zero() const {
    return x == 0 && y == 0 && z == 0;
}

double Vect::sum() const {
    return x + y + z;
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

Vect& Vect::operator+=(const Vect& u) {
    this->x += u.x;
    this->y += u.y;
    this->z += u.z;
    return *this;
}
Vect& Vect::operator-=(const Vect& u) {
    this->x -= u.x;
    this->y -= u.y;
    this->z -= u.z;
    return *this;
}
Vect& Vect::operator*=(const Vect& u) {
    this->x *= u.x;
    this->y *= u.y;
    this->z *= u.z;
    return *this;
}
Vect& Vect::operator/=(const Vect& u) {
    this->x /= u.x;
    this->y /= u.y;
    this->z /= u.z;
    return *this;
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

Vect& Vect::operator+=(double u) {
    this->x += u;
    this->y += u;
    this->z += u;
    return *this;
}
Vect& Vect::operator-=(double u) {
    this->x -= u;
    this->y -= u;
    this->z -= u;
    return *this;
}
Vect& Vect::operator*=(double u) {
    this->x *= u;
    this->y *= u;
    this->z *= u;
    return *this;
}
Vect& Vect::operator/=(double u) {
    this->x /= u;
    this->y /= u;
    this->z /= u;
    return *this;
}

bool Vect::operator==(const Vect& u) const {
    return this->x == u.x && this->y == u.y && this->z == u.z;
}
bool Vect::operator!=(const Vect& u) const {
    return !(*this == u);
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
