#include <cmath>

#include "blob.hh"
#include "tools.hh"
#include "random_color.hh"

Blob::Blob(std::vector<shared_object> obj)
    : potentiel(3),
    triangles(std::vector<Triangle>()),
    blob_objects(obj),
    cubes(std::vector<Cube>())
{
    const Point3 origin = Point3(0, 0, 0);
    init_cubes(origin, 10, 1);
}

Blob::Blob(double e, double d, double s, std::vector<shared_object> obj)
    : potentiel(s),
    triangles(std::vector<Triangle>()),
    blob_objects(obj),
    cubes(std::vector<Cube>())
{
    const Point3 origin = Point3(0, 0, 0);
    init_cubes(origin, e, d);
}

Blob::Blob(const Point3& origin, double e, double d, double s,
        std::vector<shared_object> obj)
    : potentiel(s),
    triangles(std::vector<Triangle>()),
    blob_objects(obj),
    cubes(std::vector<Cube>())
{
    init_cubes(origin, e, d);
}

void Blob::init_cubes(const Point3& orig, double e, double d) {
    // origin is the point lower left behind
    // e is the big cube
    // d pas

    for (double i = orig.x; i < orig.x + e; i += d) {
        for (double j = orig.y; j < orig.y + e; j += d) {
            for (double k = orig.z; k < orig.z + e; k +=d) {
                Cube cube;

                cube.points[0] = this->init_cube_point(i    , j + d , k);
                cube.points[1] = this->init_cube_point(i + d, j + d , k);
                cube.points[2] = this->init_cube_point(i + d, j + d , k + d);
                cube.points[3] = this->init_cube_point(i    , j + d , k + d);

                cube.points[4] = this->init_cube_point(i    , j     , k);
                cube.points[5] = this->init_cube_point(i + d, j     , k);
                cube.points[6] = this->init_cube_point(i + d, j     , k + d);
                cube.points[7] = this->init_cube_point(i    , j     , k + d);

                this->cubes.push_back(cube);
            }
        }
    }
}

Point3 Blob::init_cube_point(double i, double j, double k) const {
    Point3 p(i, j, k);
    p.iso = this->get_isolevel_at(p);
    return p;
}

void Blob::compute() {
    for (const auto& cube: this->cubes)
        this->compute_cube(cube.points);
}

void Blob::compute_cube(const Point3 p[8]) {
    Point3 vertlist[12] = { Point3() };

    int index = this->get_potentiel_index(p);
    if (edgeTable[index] == 0)
        return;

    if (edgeTable[index] & 1)
        vertlist[0] = interpolate_vertex(p[0], p[1]);
    if (edgeTable[index] & 2)
        vertlist[1] = interpolate_vertex(p[1], p[2]);
    if (edgeTable[index] & 4)
        vertlist[2] = interpolate_vertex(p[3], p[2]);
        //vertlist[2] = interpolate_vertex(p[2], p[3]);
    if (edgeTable[index] & 8)
        vertlist[3] = interpolate_vertex(p[0], p[3]);
        //vertlist[3] = interpolate_vertex(p[3], p[0]);
    if (edgeTable[index] & 16)
        vertlist[4] = interpolate_vertex(p[4], p[5]);
    if (edgeTable[index] & 32)
        vertlist[5] = interpolate_vertex(p[5], p[6]);
    if (edgeTable[index] & 64)
        vertlist[6] = interpolate_vertex(p[7], p[6]);
        //vertlist[6] = interpolate_vertex(p[6], p[7]);
    if (edgeTable[index] & 128)
        vertlist[7] = interpolate_vertex(p[4], p[7]);
        //vertlist[7] = interpolate_vertex(p[7], p[4]);
    if (edgeTable[index] & 256)
        vertlist[8] = interpolate_vertex(p[0], p[4]);
    if (edgeTable[index] & 512)
        vertlist[9] = interpolate_vertex(p[1], p[5]);
    if (edgeTable[index] & 1024)
        vertlist[10] = interpolate_vertex(p[2], p[6]);
    if (edgeTable[index] & 2048)
        vertlist[11] = interpolate_vertex(p[3], p[7]);

    for (int i=0; triTable[index][i] != -1; i+=3) {
      auto a = vertlist[triTable[index][i]];
      auto b = vertlist[triTable[index][i + 1]];
      auto c = vertlist[triTable[index][i + 2]];
      if (a == b || a == c || b == c)
          continue;
      // TODO: remove random color
      this->add_triangle(Triangle(a, b, c, r_random::random_color()));
   }
}

std::vector<Triangle> Blob::get_triangles() const {
    return triangles;
}

void Blob::add_triangle(const Triangle& t) {
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
        int obj_level = obj->get_isolevel_at(p);
        level = obj_level > level ? obj_level : level;
    }
    return level;
}
