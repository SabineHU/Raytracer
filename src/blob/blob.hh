#pragma once

#include <vector>
#include <map>
#include "triangle.hh"
#include "smooth_triangle.hh"

struct BlobCube {
    Point3 points[8] = { Point3() };
    Color colors[8] = { Color() };
    double iso[8] = { 0 };
};

class Blob {
public:
    Blob() = default;
    Blob(std::vector<shared_object>);
    Blob(double, double, double, std::vector<shared_object>);
    Blob(const Point3&, double, double, double, std::vector<shared_object>);
    Blob(const Point3&, double, double, double, std::vector<shared_object>,
            bool);

    /* Methods */
    void compute();
    void compute_cube(const BlobCube&);
    std::vector<SmoothTriangle> get_triangles() const;

private:
    void init_cube(BlobCube& blob, int n, double i, double j, double k);
    void init_cubes(const Point3& orig, double e, double d);

    void compute_vertices_properties(int, Point3*, Color*, const BlobCube&);
    void add_triangle(const SmoothTriangle&);
    int get_potentiel_index(const double* iso) const;
    Point3 interpolate_vertex(const Point3&, const Point3&, double, double);

    /* Attributes */
    double potentiel;
    std::vector<SmoothTriangle> triangles;
    std::vector<shared_object> blob_objects;
    std::vector<BlobCube> cubes;

    std::map<size_t, Vect> normals;

    bool smooth;
};
