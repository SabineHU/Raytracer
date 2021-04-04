#pragma once

#include <optional>
#include <vector>
#include <memory>

#include "object.hh"
#include "smooth_triangle.hh"

struct TriangleMesh {
    TriangleMesh() = default;
    TriangleMesh(double a, double b, double c) : x(a), y(b), z(c) {}

    double x, y, z;
};

struct Face {
    Face() = default;
    Face(const TriangleMesh& v) : vertices(v), normals(TriangleMesh()), textures(TriangleMesh()) {}
    Face(const TriangleMesh& v, const TriangleMesh& n) : vertices(v), normals(n), textures(TriangleMesh()) {}
    Face(const TriangleMesh& v, const TriangleMesh& n, const TriangleMesh& t) : vertices(v), normals(n), textures(t) {}

    /* Attributes */
    TriangleMesh vertices;
    TriangleMesh normals;
    TriangleMesh textures;
};

class Polygon : public Object {
public:
    Polygon();
    Polygon(std::vector<Vect> v, std::vector<Vect> n, std::vector<Vect2> t, std::vector<Face> f);

    virtual Vect get_normal_at(const Point3& point, double u, double v) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;
    virtual int get_isolevel_at(const Point3&) const override;

    virtual Color get_color_at(const Point3& point, double u, double v) const override;

    /* Setters / Add */
    void add_vertice(const Vect& v) { m_vertices.push_back(v); }
    void add_normal(const Vect& v) { m_normals.push_back(v); }
    void add_texture(const Vect2& v) { m_textures.push_back(v); }
    void add_face(const Face& v) { m_faces.push_back(v); }

private:
    std::vector<Vect> m_vertices;
    std::vector<Vect> m_normals;
    std::vector<Vect2> m_textures;
    std::vector<Face> m_faces;

    std::vector<std::shared_ptr<SmoothTriangle>> triangles;

    std::shared_ptr<SmoothTriangle> triangle;
    Vect normal;
};
