#pragma once

#include <vector>
#include <map>
#include "triangle.hh"
#include "smooth_triangle.hh"

struct BlobCube {
    Point3 points[8] = { Point3() };

    Color colors[8] = { Color() };
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
    void compute_cube(const Point3 p[8], const Color colors[8]);
    std::vector<SmoothTriangle> get_triangles() const;

private:
    void init_cube(BlobCube& blob, int n, double i, double j, double k);
    void init_cubes(const Point3& orig, double e, double d);

    void add_triangle(const SmoothTriangle&);
    int get_potentiel_index(const Point3* p) const;
    Point3 interpolate_vertex(const Point3& p1, const Point3& p2);

    Color get_iso_and_color_at(const Point3& p) const;

    /* Attributes */
    double potentiel;
    std::vector<SmoothTriangle> triangles;
    std::vector<shared_object> blob_objects;
    std::vector<BlobCube> cubes;

    std::map<size_t, Vect> normals;

    bool smooth;
};
