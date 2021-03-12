#pragma once

#include <vector>
#include "triangle.hh"

class Blob {
public:
    Blob();
    Blob(double, double, double);
    Blob(const Point3&, double, double, double);

    void compute_cube(const Point3* p, double s);

private:
    void add_triangle(const Triangle&);
    int get_potentiel_index(const Point3* p, double s) const;
    Point3 interpolate_vertex(double s, const Point3& p1, const Point3& p2);

public:
    /* Attributes */
    Point3 lower_left;
    double side;
    double dis;

    double potentiel;

    std::vector<Triangle> triangles;
};
