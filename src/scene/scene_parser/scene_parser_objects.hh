#pragma once

#include <iostream>
#include <vector>

#include "json.hpp"

#include "capped_cone.hh"
#include "capsule.hh"
#include "cone.hh"
#include "CSG.hh"
#include "cube.hh"
#include "cylinder.hh"
#include "ellipsoid.hh"
#include "plane.hh"
#include "plane_holed.hh"
#include "sphere.hh"

#include "blob.hh"
#include "loader.hh"
#include "polygon.hh"

#include "scene_parser_utils.hh"
#include "scene_parser_texture.hh"

inline std::vector<shared_object> parse_objects(const nlohmann::json& json);

static shared_object parse_sphere(const nlohmann::json& json) {
    check_missing_field(json, "center");
    check_missing_field(json, "radius");

    Vect center = parse_vect(json["center"]);
    double radius = json["radius"];

    return std::make_shared<Sphere>(Sphere(center, radius));
}

static shared_object parse_capped_cone(const nlohmann::json& json) {
    check_missing_field(json, "bottom");
    check_missing_field(json, "top");
    check_missing_field(json, "radius_bottom");
    check_missing_field(json, "radius_top");

    Point3 bottom = parse_vect(json["bottom"]);
    Point3 top = parse_vect(json["top"]);
    double radius_bottom = json["radius_bottom"];
    double radius_top = json["radius_top"];

    return std::make_shared<CappedCone>(CappedCone(bottom, top, radius_bottom, radius_top));
}

static shared_object parse_capsule(const nlohmann::json& json) {
    check_missing_field(json, "bottom");
    check_missing_field(json, "top");
    check_missing_field(json, "radius");

    Point3 bottom = parse_vect(json["bottom"]);
    Point3 top = parse_vect(json["top"]);
    double radius = json["radius"];

    return std::make_shared<Capsule>(Capsule(bottom, top, radius));
}

static shared_object parse_cone(const nlohmann::json& json) {
    check_missing_field(json, "position");
    check_missing_field(json, "radius");
    check_missing_field(json, "height");

    Point3 position = parse_vect(json["position"]);
    double radius = json["radius"];
    double height = json["height"];

    return std::make_shared<Cone>(Cone(position, radius, height));
}

static shared_object parse_cube(const nlohmann::json& json) {
    check_missing_field(json, "position");
    check_missing_field(json, "side");

    Point3 position = parse_vect(json["position"]);
    double side = json["side"];

    return std::make_shared<Cube>(Cube(position, side));
}

static shared_object parse_cylinder(const nlohmann::json& json) {
    check_missing_field(json, "bottom");
    check_missing_field(json, "top");
    check_missing_field(json, "radius");

    Point3 bottom = parse_vect(json["bottom"]);
    Point3 top = parse_vect(json["top"]);
    double radius = json["radius"];

    return std::make_shared<Cylinder>(Cylinder(bottom, top, radius));
}

static shared_object parse_ellipsoid(const nlohmann::json& json) {
    check_missing_field(json, "center");
    check_missing_field(json, "radius");

    Point3 center = parse_vect(json["center"]);
    Point3 radius = parse_vect(json["radius"]);

    return std::make_shared<Ellipsoid>(Ellipsoid(center, radius));
}

static shared_object parse_plane(const nlohmann::json& json, bool is_holed) {
    check_missing_field(json, "normal");
    check_missing_field(json, "distance");

    Point3 normal = parse_vect(json["normal"]);
    double distance = json["distance"];

    std::shared_ptr<Plane> plane;
    if (is_holed)
        plane = std::make_shared<PlaneHoled>(PlaneHoled(normal, distance));
    else
        plane = std::make_shared<Plane>(Plane(normal, distance));

    if (has_field(json, "width")) {
        double width = json["width"];
        plane->set_width(width);
    }

    if (has_field(json, "height")) {
        double height = json["height"];
        plane->set_height(height);
    }

    return plane;
}

static shared_object parse_polygon(const nlohmann::json& json) {
    check_missing_field(json, "obj_asset");
    check_missing_field(json, "mtl_asset");

    const std::string& obj_asset = json["obj_asset"];
    const std::string& mtl_asset = json["mtl_asset"];

    auto mat = parse_materials(mtl_asset);
    auto p = parse_obj_to_polygon(obj_asset, mat);
    return std::make_shared<Polygon>(p);
}

static Blob parse_blob(const nlohmann::json& json) {
    check_missing_field(json, "point");
    check_missing_field(json, "objects");
    check_missing_field(json, "e");
    check_missing_field(json, "d");
    check_missing_field(json, "s");
    check_missing_field(json, "smooth");

    Point3 point = parse_vect(json["point"]);
    auto objects = parse_objects(json["objects"]);
    bool smooth = json["smooth"];
    double e = json["e"];
    double d = json["d"];
    double s = json["s"];

    auto blob = Blob(point, e, d, s, objects, smooth);
    blob.compute();

    return blob;
}

static void parse_object_properties(const nlohmann::json &json, shared_object object) {
    if (has_field(json, "texture")) {
        auto texture = parse_texture(json["texture"]);
        object->set_texture(texture);
    }

    if (has_field(json, "bump_mappings"))
        parse_bump_mappings(json["bump_mappings"], object);

    if (has_field(json, "specular")) {
        double specular = json["specular"];
        object->set_specular(specular);
    }

    if (has_field(json, "ior")) {
        double ior = json["ior"];
        object->set_ior(ior);
    }

    if (has_field(json, "displacement_image")) {
        auto texture = parse_image_texture(json["displacement_image"]);
        object->set_displacement_image(texture);
    }

}

static shared_object parse_object(const nlohmann::json& json) {
    auto object_type = json["type"];

    shared_object object;

    if (object_type == "sphere")
        object = parse_sphere(json);
    else if (object_type == "capped_cone")
        object = parse_capped_cone(json);
    else if (object_type == "capsule")
        object = parse_capsule(json);
    else if (object_type == "cone")
        object = parse_cone(json);
    else if (object_type == "cube")
        object = parse_cube(json);
    else if (object_type == "cylinder")
        object = parse_cylinder(json);
    else if (object_type == "ellipsoid")
        object = parse_ellipsoid(json);
    else if (object_type == "plane")
        object = parse_plane(json, false);
    else if (object_type == "plane_holed")
        object = parse_plane(json, true);
    else if (object_type == "polygon")
        object = parse_polygon(json);
    else {
        std::cerr << "Unsupported object " << object_type << "!\n";
        exit(1);
    }

    parse_object_properties(json, object);
    return object;
}

static shared_object parse_csg(const nlohmann::json& json) {
    shared_object obj1 = parse_object(json["obj1"]);
    shared_object obj2 = parse_object(json["obj2"]);

    auto csg_type = json["type"];
    if (csg_type == "UNION")
        return std::make_shared<CSG>(UNION, obj1, obj2);
    if (csg_type == "INTERSECTION")
        return std::make_shared<CSG>(INTERSECTION, obj1, obj2);
    if (csg_type == "MINUS")
        return std::make_shared<CSG>(MINUS, obj1, obj2);
    if (csg_type == "DIFFERENCE")
        return std::make_shared<CSG>(DIFFERENCE, obj1, obj2);

    std::cerr << "Unsupported CSG object \"" << csg_type << "\"!\n";
    exit(1);
}

inline std::vector<shared_object> parse_objects(const nlohmann::json& json)
{
    std::vector<shared_object> objects;

    for (const auto& object : json) {
        auto object_type = object["type"];

        if (object_type == "blob") {
            Blob blob = parse_blob(object);
            for (auto& triangle: blob.get_triangles())
                objects.push_back(std::make_shared<SmoothTriangle>(triangle));
        } else if (object_type == "CSG") {
            objects.push_back(parse_csg(object["CSG"]));
        }
        else
            objects.push_back(parse_object(object));
    }

    return objects;
}
