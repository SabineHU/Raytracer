#include <cmath>

#include "blob.hh"
#include "tools.hh"
#include "random_color.hh"

Blob::Blob()
    : side(10), dis(1), potentiel(1), triangles(std::vector<Triangle>())
{
    lower_left = Point3(0, 0, 0);
}

Blob::Blob(double e, double d, double s)
    : side(e), dis(d), potentiel(s), triangles(std::vector<Triangle>())
{
    lower_left = Point3(0, 0, 0);
}

Blob::Blob(const Point3& p, double e, double d, double s)
    : lower_left(p), side(e), dis(d), potentiel(s),
    triangles(std::vector<Triangle>())
{}


void Blob::compute_cube(const Point3* p, double s) {
    Point3 vertlist[12] = { Point3() };

    int index = this->get_potentiel_index(p, s);
    if (edgeTable[index] == 0)
        return;

    if (edgeTable[index] & 1)
        vertlist[0] = interpolate_vertex(s, p[0], p[1]);
    if (edgeTable[index] & 2)
        vertlist[1] = interpolate_vertex(s, p[1], p[2]);
    if (edgeTable[index] & 4)
        vertlist[2] = interpolate_vertex(s, p[2], p[3]);
    if (edgeTable[index] & 8)
        vertlist[3] = interpolate_vertex(s, p[3], p[0]);
    if (edgeTable[index] & 16)
        vertlist[4] = interpolate_vertex(s, p[4], p[5]);
    if (edgeTable[index] & 32)
        vertlist[5] = interpolate_vertex(s, p[5], p[6]);
    if (edgeTable[index] & 64)
        vertlist[6] = interpolate_vertex(s, p[6], p[7]);
    if (edgeTable[index] & 128)
        vertlist[7] = interpolate_vertex(s, p[7], p[4]);
    if (edgeTable[index] & 256)
        vertlist[8] = interpolate_vertex(s, p[0], p[4]);
    if (edgeTable[index] & 512)
        vertlist[9] = interpolate_vertex(s, p[1], p[5]);
    if (edgeTable[index] & 1024)
        vertlist[10] = interpolate_vertex(s, p[2], p[6]);
    if (edgeTable[index] & 2048)
        vertlist[11] = interpolate_vertex(s, p[3], p[7]);

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

void Blob::add_triangle(const Triangle& t) {
    this->triangles.push_back(t);
}

int Blob::get_potentiel_index(const Point3* p, double s) const {
    int index = 0;
    if (p[0].iso < s) index |= 1;
    if (p[1].iso < s) index |= 2;
    if (p[2].iso < s) index |= 4;
    if (p[3].iso < s) index |= 8;
    if (p[4].iso < s) index |= 16;
    if (p[5].iso < s) index |= 32;
    if (p[6].iso < s) index |= 64;
    if (p[7].iso < s) index |= 128;
    return index;
}

Point3 Blob::interpolate_vertex(double s, const Point3& p1, const Point3& p2) {

   if (std::abs(s - p1.iso) < 0.00001)
      return p1;
   if (std::abs(s - p2.iso) < 0.00001)
      return p2;
   if (std::abs(p1.iso - p2.iso) < 0.00001)
      return p1;
   double mu = (s - p1.iso) / (p2.iso - p1.iso);
   return p1 + (p2 - p1) * mu;
}
