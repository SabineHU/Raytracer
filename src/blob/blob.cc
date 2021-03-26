#include <cmath>
#include <iostream>

#include "blob.hh"
#include "tools.hh"
#include "random_color.hh"
#include "hash.hh"
#include "vector3_op.hh"

Blob::Blob(std::vector<shared_object> obj)
    : potentiel(3),
    triangles(std::vector<SmoothTriangle>()),
    blob_objects(obj),
    cubes(std::vector<BlobCube>()),
    smooth(false)
{
    const Point3 origin = Point3(0, 0, 0);
    init_cubes(origin, 10, 1);
}

Blob::Blob(double e, double d, double s, std::vector<shared_object> obj)
    : potentiel(s),
    triangles(std::vector<SmoothTriangle>()),
    blob_objects(obj),
    cubes(std::vector<BlobCube>()),
    smooth(false)
{
    const Point3 origin = Point3(0, 0, 0);
    init_cubes(origin, e, d);
}

Blob::Blob(const Point3& origin, double e, double d, double s,
        std::vector<shared_object> obj)
    : potentiel(s),
    triangles(std::vector<SmoothTriangle>()),
    blob_objects(obj),
    cubes(std::vector<BlobCube>()),
    smooth(false)
{
    init_cubes(origin, e, d);
}


Blob::Blob(const Point3& orig, double e, double d, double s,
        std::vector<shared_object> obj, bool smooth_)
    : potentiel(s),
    triangles(std::vector<SmoothTriangle>()),
    blob_objects(obj),
    cubes(std::vector<BlobCube>()),
    smooth(smooth_)
{
    init_cubes(orig, e, d);
}

void Blob::init_cubes(const Point3& orig, double e, double d) {
    // origin is the point lower left behind
    // e is the big cube
    // d pas
    if (this->blob_objects.size() == 0)
        return;

    double e2 = e / 2;
    for (double i = orig.x - e2; i < orig.x + e2; i += d) {
        for (double j = orig.y - e2; j < orig.y + e2; j += d) {
            for (double k = orig.z - e2; k < orig.z + e2; k +=d) {
                BlobCube cube;

                init_cube(cube, 0, i    , j + d , k);
                init_cube(cube, 1, i + d, j + d , k);
                init_cube(cube, 2, i + d, j + d , k + d);
                init_cube(cube, 3, i    , j + d , k + d);

                init_cube(cube, 4, i    , j     , k);
                init_cube(cube, 5, i + d, j     , k);
                init_cube(cube, 6, i + d, j     , k + d);
                init_cube(cube, 7, i    , j     , k + d);

                this->cubes.push_back(cube);
            }
        }
    }
}

void Blob::init_cube(BlobCube& blob, int n, double i, double j, double k) {
    /* Initialize point, get color and iso */
    Point3 p(i, j, k);
    Color color = this->get_iso_and_color_at(p);

    p.iso = color.iso;
    color.iso = 0;

    blob.points[n] = p;
    blob.colors[n] = color;
}

Point3 Blob::init_cube_point(double i, double j, double k) const {
    Point3 p(i, j, k);
    p.iso = this->get_isolevel_at(p);
    return p;
}

void Blob::compute() {
    for (const auto& cube: this->cubes) {
        this->compute_cube(cube.points, cube.colors);
    }

    if (this->smooth) {
        for (auto& [key, value] : this->normals) {
            value = value.normalize();
            // / value.second;
        }

        for (auto& triangle: this->triangles) {
            triangle.normalA = this->normals[hash::get_point_hash(triangle.A)];
            triangle.normalB = this->normals[hash::get_point_hash(triangle.B)];
            triangle.normalC = this->normals[hash::get_point_hash(triangle.C)];
        }
    }
}

void Blob::compute_cube(const Point3 p[8], const Color colors[8]) {
    Point3 vertlist[12] = { Point3() };
    Color vertcolor[12] = { Color() };

    int index = this->get_potentiel_index(p);
    if (edgeTable[index] == 0)
        return;

    if (edgeTable[index] & 1) {
        vertlist[0] = interpolate_vertex(p[0], p[1]);
        vertcolor[0] = (colors[0] + colors[1]) / 2;
    }
    if (edgeTable[index] & 2) {
        vertlist[1] = interpolate_vertex(p[1], p[2]);
        vertcolor[1] = (colors[1] + colors[2]) / 2;
    }
    if (edgeTable[index] & 4) {
        vertlist[2] = interpolate_vertex(p[3], p[2]);
        vertcolor[2] = (colors[3] + colors[2]) / 2;
    }
    if (edgeTable[index] & 8) {
        vertlist[3] = interpolate_vertex(p[0], p[3]);
        vertcolor[3] = (colors[0] + colors[3]) / 2;
    }
    if (edgeTable[index] & 16) {
        vertlist[4] = interpolate_vertex(p[4], p[5]);
        vertcolor[4] = (colors[4] + colors[5]) / 2;
    }
    if (edgeTable[index] & 32) {
        vertlist[5] = interpolate_vertex(p[5], p[6]);
        vertcolor[5] = (colors[5] + colors[6]) / 2;
    }
    if (edgeTable[index] & 64) {
        vertlist[6] = interpolate_vertex(p[7], p[6]);
        vertcolor[6] = (colors[7] + colors[6]) / 2;
    }
    if (edgeTable[index] & 128) {
        vertlist[7] = interpolate_vertex(p[4], p[7]);
        vertcolor[7] = (colors[4] + colors[7]) / 2;
    }
    if (edgeTable[index] & 256) {
        vertlist[8] = interpolate_vertex(p[0], p[4]);
        vertcolor[8] = (colors[0] + colors[4]) / 2;
    }
    if (edgeTable[index] & 512) {
        vertlist[9] = interpolate_vertex(p[1], p[5]);
        vertcolor[9] = (colors[1] + colors[5]) / 2;
    }
    if (edgeTable[index] & 1024) {
        vertlist[10] = interpolate_vertex(p[2], p[6]);
        vertcolor[10] = (colors[2] + colors[6]) / 2;
    }
    if (edgeTable[index] & 2048) {
        vertlist[11] = interpolate_vertex(p[3], p[7]);
        vertcolor[11] = (colors[3] + colors[7]) / 2;
    }

    for (int i = 0; triTable[index][i] != -1; i += 3) {
        auto a = vertlist[triTable[index][i]];
        auto b = vertlist[triTable[index][i + 1]];
        auto c = vertlist[triTable[index][i + 2]];
        if (a == b || a == c || b == c)
            continue;
        // TODO: remove random color

        auto color = (vertcolor[triTable[index][i]]
            + vertcolor[triTable[index][i + 1]]
            + vertcolor[triTable[index][i + 2]]) / 3;

        auto triangle = SmoothTriangle(a, b, c, color);
        this->add_triangle(triangle);

        if (this->smooth) {

            size_t sa = hash::get_point_hash(a);
            size_t sb = hash::get_point_hash(b);
            size_t sc = hash::get_point_hash(c);

            if (this->normals.find(sa) == this->normals.end())
                this->normals[sa] = Vect(0, 0, 0);
            if (this->normals.find(sb) == this->normals.end())
                this->normals[sb] = Vect(0, 0, 0);
            if (this->normals.find(sc) == this->normals.end())
                this->normals[sc] = Vect(0, 0, 0);

            //auto normal = triangle.get_normal_at(Point3());
            auto normal = vector::cross(c - a, b - a);

            this->normals[sa] += normal;
            this->normals[sb] += normal;
            this->normals[sc] += normal;
        }
    }
}

std::vector<SmoothTriangle> Blob::get_triangles() const {
    return triangles;
}

void Blob::add_triangle(const SmoothTriangle& t) {
    this->triangles.push_back(t);
}

int Blob::get_potentiel_index(const Point3* p) const {
    int index = 0;
    if (p[0].iso < this->potentiel) index |= 1;
    if (p[1].iso < this->potentiel) index |= 2;
    if (p[2].iso < this->potentiel) index |= 4;
    if (p[3].iso < this->potentiel) index |= 8;
    if (p[4].iso < this->potentiel) index |= 16;
    if (p[5].iso < this->potentiel) index |= 32;
    if (p[6].iso < this->potentiel) index |= 64;
    if (p[7].iso < this->potentiel) index |= 128;
    return index;
}

Point3 Blob::interpolate_vertex(const Point3& p1, const Point3& p2) {

   if (std::abs(this->potentiel - p1.iso) < 0.00001)
      return p1;
   if (std::abs(this->potentiel - p2.iso) < 0.00001)
      return p2;
   if (std::abs(p1.iso - p2.iso) < 0.00001)
      return p1;
   double mu = (this->potentiel - p1.iso) / (p2.iso - p1.iso);
   return p1 + (p2 - p1) * mu;
}

int Blob::get_isolevel_at(const Point3& p) const {
    int level = 0;
    for (const auto& obj : this->blob_objects) {
        //int obj_level = obj->get_isolevel_at(p);
        //level = obj_level < level ? obj_level : level;
        level += obj->get_isolevel_at(p);
    }
    return level / this->blob_objects.size();
}

Color Blob::get_iso_and_color_at(const Point3& p) const {
    Color color;
    int level = 0;
    for (const auto& obj : this->blob_objects) {
        auto iso = obj->get_isolevel_at(p);
        level += iso;
        color += obj->texture->get_color(p, 0, 0) * (1 - iso / 100);
    }
    color /= this->blob_objects.size();
    level /= this->blob_objects.size();
    color.iso = level;
    return color;
}
