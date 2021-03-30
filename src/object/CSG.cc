#include "CSG.hh"
#include "lambertian.hh"

CSG::CSG(ObjectOperator o, shared_object s1, shared_object s2)
    : op(o), obj1(s1), obj2(s2), obj1_closest(false)
{
    texture = nullptr;
    specular = 0;
}

Vect CSG::get_normal_at(const Vect& point) const {
    return obj1_closest ? obj1->get_normal_at(point) : obj2->get_normal_at(point);
}

bool CSG::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    double t_max1 = t_max;
    double t_max2 = t_max;
    IntersectionInfo info1;
    IntersectionInfo info2;
    bool found1 = false;
    bool found2 = false;
    switch (op) {
        case UNION:
            if (obj1->find_intersection(ray, t_min, t_max1, info1)) found1 = true;
            if (obj2->find_intersection(ray, t_min, t_max2, info2)) found2 = true;

            /* No intersections */
            if (!found1 && !found2) return false;

            /* Intersect both */
            if (found1 && found2) {
                if (t_max1 < t_max2) obj1_closest = true;
                else obj1_closest = false;
                t_max = std::min(t_max1, t_max2);
                info.t_min = std::min(info1.t_min, info2.t_min);
                info.t_max = std::max(info1.t_max, info2.t_max);
                return true;
            }

            if (found1) {
                t_max = t_max1;
                info.t_min = info1.t_min;
                info.t_max = info1.t_max;
                obj1_closest = true;
            }

            if (found2) {
                t_max = t_max2;
                info.t_min = info2.t_min;
                info.t_max = info2.t_max;
                obj1_closest = false;
            }
            return true;

        case INTERSECTION:
            // Intersection for each obj
            if (!obj1->find_intersection(ray, t_min, t_max1, info1)) return false;
            if (!obj2->find_intersection(ray, t_min, t_max2, info2)) return false;

            // Get min t
            if (info2.t_min < info1.t_min && info1.t_min < info2.t_max) {
                t_max = info1.t_min;
                obj1_closest = true;

                info.t_min = info2.t_min;
                info.t_max = info2.t_max;
                return true;
            } else if (info1.t_min < info2.t_min && info2.t_min < info1.t_max) {
                t_max = info2.t_min;
                obj1_closest = false;

                info.t_min = info1.t_min;
                info.t_max = info1.t_max;
                return true;
            }
            return false;

        case MINUS:
            // Intersection for each obj
            if (obj1->find_intersection(ray, t_min, t_max1, info1)) found1 = true;
            if (obj2->find_intersection(ray, t_min, t_max2, info2)) found2 = true;

            if (!found1) return false;

            /* Intersect both */
            if (found2) {
                return false;
            }

            t_max = t_max1;
            obj1_closest = true;
            return true;

        default:
            if (obj1->find_intersection(ray, t_min, t_max1, info1)) found1 = true;
            if (obj2->find_intersection(ray, t_min, t_max2, info2)) found2 = true;

            /* No intersection */
            if (!found1 && !found2) return false;

            /* Intersect one object */
            if (found1 && !found2) {
                t_max = info1.t_min;
                obj1_closest = true;
                return true;
            }

            if (!found1 && found2) {
                t_max = info2.t_min;
                obj1_closest = false;
                return true;
            }

            /* Intersect both */
            if (info1.t_min < info2.t_min && info1.t_max < info2.t_max) {
                t_max = info2.t_min;
                obj1_closest = true;
                return true;
            }
            if (info2.t_min < info1.t_min && info2.t_max < info1.t_max) {
                t_max = info2.t_max;
                obj1_closest = false;
                return true;
            }
            return false;
    }
}

Color CSG::get_color_at(const Point3& p, double u, double v) const {
    return obj1_closest ? obj1->get_color_at(p, u, v) : obj2->get_color_at(p, u, v);
}

shared_texture CSG::get_texture() const {
    return obj1_closest ? obj1->get_texture() : obj2->get_texture();
}

int CSG::get_isolevel_at(const Point3& p) const {
    return std::min(obj1->get_isolevel_at(p), obj2->get_isolevel_at(p));
}
