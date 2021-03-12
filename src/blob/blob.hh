#pragma once

#include <vector>
#include "triangle.hh"

class Blob {
public:
    Blob();
    Blob(double, double, double);
    Blob(const Point3&, double, double, double);

    void compute_cube(double* values, Point3* p, double s);

private:
    void add_triangle(const Triangle&);
    void get_potentiel_index(double* value, double s, int& index) const;
    Point3 interpolate_vertex(double s, Point3 p1, Point3 p2, double valp1, double valp2);

public:
    /* Attributes */
    Point3 lower_left;
    double side;
    double dis;

    double potentiel;

    std::vector<Triangle> triangles;
};
