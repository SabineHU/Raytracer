#include "polygon.hh"

#include "smooth_triangle.hh"

Polygon::Polygon()
    : Object(), triangle(nullptr)
{}

Polygon::Polygon(std::vector<Vect> vertices, std::vector<Vect> normals,
        std::vector<Vect2> textures, std::vector<Face> faces)
    : Object(), m_vertices(vertices), m_normals(normals), m_textures(textures), m_faces(faces)
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

Vect Polygon::get_normal_at(const Point3& p, double u, double v) const {
    return triangle->get_normal_at(p, u, v);
}

bool Polygon::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    bool found = false;
    for (auto &t : this->triangles)
        if (t->find_intersection(ray, t_min, t_max, info)) {
            this->triangle = t;
            found = true;
    }

    return found;
}

Color Polygon::get_color_at(const Point3& p, double u, double v) const {
    return triangle->get_color_at(p, u, v);
}
