#pragma once

#include <vector>
#include "triangle.hh"

struct Cube {
    Point3 points[8] = { Point3() };
};

class Blob {
public:
    Blob() = default;
    Blob(std::vector<shared_object>);
    Blob(double, double, double, std::vector<shared_object>);
    Blob(const Point3&, double, double, double, std::vector<shared_object>);
    /* Methods */
    void compute();
    void compute_cube(const Point3 p[8]);
    std::vector<Triangle> get_triangles() const;

private:
    void init_cubes(const Point3& orig, double e, double d);
    Point3 init_cube_point(double i, double j, double k) const;

    void add_triangle(const Triangle&);
    int get_potentiel_index(const Point3* p) const;
    Point3 interpolate_vertex(const Point3& p1, const Point3& p2);

    int get_isolevel_at(const Point3&) const;

    /* Attributes */
    double potentiel;
    std::vector<Triangle> triangles;
    std::vector<shared_object> blob_objects;
    std::vector<Cube> cubes;

};