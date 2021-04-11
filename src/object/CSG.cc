#include "CSG.hh"
#include "lambertian.hh"

CSG::CSG(ObjectOperator o, shared_object s1, shared_object s2)
    : op(o), obj1(s1), obj2(s2)
{
    texture = nullptr;
    specular = 0;
}

bool CSG::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const {
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
                if (t_max1 < t_max2) {
                    info = info1;
                } else {
                    info = info2;
                }

                t_max = std::min(t_max1, t_max2);
                info.t_min = std::min(info1.t_min, info2.t_min);
                info.t_max = std::max(info1.t_max, info2.t_max);
            } else if (found1) {
                t_max = t_max1;
                info = info1;
                info.t_min = info1.t_min;
                info.t_max = info1.t_max;
            } else if (found2) {
                t_max = t_max2;
                info = info2;
                info.t_min = info2.t_min;
                info.t_max = info2.t_max;
            }

            info.point = ray.origin + ray.direction * t_max;

            return true;

        case INTERSECTION:
            // Intersection for each obj
            if (!obj1->find_intersection(ray, t_min, t_max1, info1)) return false;
            if (!obj2->find_intersection(ray, t_min, t_max2, info2)) return false;

            // Get min t
            if (info2.t_min < info1.t_min && info1.t_min < info2.t_max)
            {
                t_max = info1.t_min;
                info = info1;

                info.t_min = info2.t_min;
                info.t_max = info2.t_max;
                info.point = ray.origin + ray.direction * t_max;

                return true;
            }
            else if (info1.t_min < info2.t_min && info2.t_min < info1.t_max)
            {
                t_max = info2.t_min;
                info = info2;

                info.t_min = info1.t_min;
                info.t_max = info1.t_max;
                info.point = ray.origin + ray.direction * t_max;

                return true;
            }

            return false;

        case MINUS:
            // Intersection for each obj
            if (obj1->find_intersection(ray, t_min, t_max1, info1)) found1 = true;
            if (obj2->find_intersection(ray, t_min, t_max2, info2)) found2 = true;

            if (!found1) return false;
            if (!found2)
            {
                t_max = t_max1;
                info = info1;
                info.point = ray.origin + ray.direction * t_max;

                return true;
            }

            /* Intersect both */
            /* Right closer */
            if (info2.t_max < info1.t_min)
            {
                t_max = info1.t_min;
                info = info1;
                info.point = ray.origin + ray.direction * t_max;

                return true;
            }
            /* Left closer */
            if (info1.t_max < info2.t_min)
            {
                t_max = info1.t_min;
                info = info1;
                info.point = ray.origin + ray.direction * t_max;

                return true;
            }
            if (info1.t_min < info2.t_min)
            {
                t_max = info1.t_min;
                info = info1;
                info.point = ray.origin + ray.direction * t_max;

                return true;
            }

            if (info2.t_max < info1.t_max) {
                t_max = info2.t_max;
                info = info2;
                info.point = ray.origin + ray.direction * t_max;

                return true;
            }

            return false;

        default:
            if (obj1->find_intersection(ray, t_min, t_max1, info1)) found1 = true;
            if (obj2->find_intersection(ray, t_min, t_max2, info2)) found2 = true;

            /* No intersection */
            if (!found1 && !found2) return false;

            /* Intersect one object */
            if (found1 && !found2)
            {
                t_max = info1.t_min;
                info = info1;
                info.point = ray.origin + ray.direction * t_max;

                return true;
            }

            if (!found1 && found2)
            {
                t_max = info2.t_min;
                info = info2;
                info.point = ray.origin + ray.direction * t_max;

                return true;
            }

            /* Intersect both */
            if (info1.t_min < info2.t_min && info1.t_max < info2.t_max)
            {
                t_max = info2.t_min;
                info = info1;
                info.point = ray.origin + ray.direction * t_max;

                return true;
            }
            if (info2.t_min < info1.t_min && info2.t_max < info1.t_max)
            {
                t_max = info2.t_max;
                info = info2;
                info.point = ray.origin + ray.direction * t_max;

                return true;
            }

            return false;
    }
}
