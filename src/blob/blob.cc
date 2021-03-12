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


void Blob::compute_cube(double* values, Point3* p, double s) {
    // values
    // p = points
    int index = 0;
    Point3 vertlist[12] = { Point3() };

    this->get_potentiel_index(values, s, index);
    if (edgeTable[index] == 0)
        return;

    if (edgeTable[index] & 1)
        vertlist[0] = interpolate_vertex(s, p[0], p[1], values[0], values[1]);
    if (edgeTable[index] & 2)
        vertlist[1] = interpolate_vertex(s, p[1], p[2], values[1], values[2]);
    if (edgeTable[index] & 4)
        vertlist[2] = interpolate_vertex(s, p[2], p[3], values[2], values[3]);
    if (edgeTable[index] & 8)
        vertlist[3] = interpolate_vertex(s, p[3], p[0], values[3], values[0]);
    if (edgeTable[index] & 16)
        vertlist[4] = interpolate_vertex(s, p[4], p[5], values[4], values[5]);
    if (edgeTable[index] & 32)
        vertlist[5] = interpolate_vertex(s, p[5], p[6], values[5], values[6]);
    if (edgeTable[index] & 64)
        vertlist[6] = interpolate_vertex(s, p[6], p[7], values[6], values[7]);
    if (edgeTable[index] & 128)
        vertlist[7] = interpolate_vertex(s, p[7], p[4], values[7], values[4]);
    if (edgeTable[index] & 256)
        vertlist[8] = interpolate_vertex(s, p[0], p[4], values[0], values[4]);
    if (edgeTable[index] & 512)
        vertlist[9] = interpolate_vertex(s, p[1], p[5], values[1], values[5]);
    if (edgeTable[index] & 1024)
        vertlist[10] = interpolate_vertex(s, p[2], p[6], values[2], values[6]);
    if (edgeTable[index] & 2048)
        vertlist[11] = interpolate_vertex(s, p[3], p[7], values[3], values[7]);

    for (int i=0; triTable[index][i] != -1; i+=3) {
      auto a = vertlist[triTable[index][i  ]];
      auto b = vertlist[triTable[index][i+1]];
      auto c = vertlist[triTable[index][i+2]];
      // TODO: remove random color
      this->add_triangle(Triangle(a, b, c, r_random::random_color()));
   }
}

void Blob::add_triangle(const Triangle& t) {
    this->triangles.push_back(t);
}

void Blob::get_potentiel_index(double* value, double s, int& index) const {
    if (value[0] < s) index |= 1;
    if (value[1] < s) index |= 2;
    if (value[2] < s) index |= 4;
    if (value[3] < s) index |= 8;
    if (value[4] < s) index |= 16;
    if (value[5] < s) index |= 32;
    if (value[6] < s) index |= 64;
    if (value[7] < s) index |= 128;
}

Point3 Blob::interpolate_vertex(double s, Point3 p1, Point3 p2, double valp1, double valp2) {

   if (std::abs(s-valp1) < 0.00001)
      return p1;
   if (std::abs(s-valp2) < 0.00001)
      return p2;
   if (std::abs(valp1-valp2) < 0.00001)
      return p1;
   double mu = (s - valp1) / (valp2 - valp1);
   auto x = p1.x + mu * (p2.x - p1.x);
   auto y = p1.y + mu * (p2.y - p1.y);
   auto z = p1.z + mu * (p2.z - p1.z);
   return Point3(x, y, z);
}
