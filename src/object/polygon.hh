#pragma once

#include <optional>
#include <vector>
#include <memory>
#include <string>

#include "object.hh"
#include "smooth_triangle.hh"

struct TriangleMesh {
    TriangleMesh() = default;
    TriangleMesh(double a, double b, double c) : x(a), y(b), z(c) {}

    double x, y, z;
};

struct Material {
    Material() = default;

    double ns;
    Color ka;
    Color kd;
    Color ks;
    Color ke;
};

struct Face {
    Face() = default;
    Face(const TriangleMesh& v, const TriangleMesh& n, const TriangleMesh& t, const Material& m)
        : vertices(v), normals(n), textures(t), material(m) {}

    /* Attributes */
    TriangleMesh vertices;
    TriangleMesh normals;
    TriangleMesh textures;

    Material material;
};

class Polygon : public Object {
public:
    Polygon();
    Polygon(std::vector<Vect> v, std::vector<Vect> n, std::vector<Vect2> t, std::vector<Face> f);

    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const override;

private:
    std::vector<std::shared_ptr<SmoothTriangle>> triangles;
};
