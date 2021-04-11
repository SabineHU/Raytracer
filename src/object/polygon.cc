#include "polygon.hh"

#include "smooth_triangle.hh"

Polygon::Polygon()
    : Object()
{}

Polygon::Polygon(std::vector<Vect> vertices, std::vector<Vect> normals,
        std::vector<Vect2> textures, std::vector<Face> faces)
    : Object()
{
    this->triangles = std::vector<std::shared_ptr<SmoothTriangle>>();

    for (const auto& face : faces) {
        Point3 a = vertices[face.vertices.x];
        Point3 b = vertices[face.vertices.y];
        Point3 c = vertices[face.vertices.z];

        Point3 na = normals[face.normals.x];
        Point3 nb = normals[face.normals.y];
        Point3 nc = normals[face.normals.z];

        SmoothTriangle triangle;
        if (na == nb && na == nc)
            triangle = SmoothTriangle(a, b, c);
        else
            triangle = SmoothTriangle(a, b, c, na, nb, nc);
        triangle.set_texture(face.material.kd / 2);
        triangles.push_back(std::make_shared<SmoothTriangle>(triangle));
    }
}

bool Polygon::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const {
    bool found = false;
    for (auto &t : this->triangles)
        if (t->find_intersection(ray, t_min, t_max, info)) {
            found = true;
    }

    return found;
}
