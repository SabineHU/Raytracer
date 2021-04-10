#include <memory>

#include "scene_parser.hh"
#include "json.hpp"
#include "file.hh"
#include "scene_parser_utils.hh"
#include "scene_parser_camera.hh"
#include "scene_parser_objects.hh"
#include "scene_parser_lights.hh"

SceneParser::SceneParser(const std::string& path)
    : _path(path)
{}

static nlohmann::json parse_json_file(const std::string& filename) {
    auto file = file::open_file(filename);
    auto json = nlohmann::json::parse(file);
    file.close();
    return json;
}

static void parse_background_colors(const nlohmann::json& json, Scene& scene) {
    if (!has_field(json, "backgrounds_colors"))
        return;

    auto backgrounds_colors = json["backgrounds_colors"];

    check_missing_field(backgrounds_colors, "color1");
    check_missing_field(backgrounds_colors, "color2");

    auto color1 = parse_color(backgrounds_colors["color1"]);
    auto color2 = parse_color(backgrounds_colors["color2"]);

    scene.set_background_colors(color1, color2);
}

static void parse_fog(const nlohmann::json& json, Scene& scene) {
    if (!has_field(json, "fog"))
        return;

    auto fog = json["fog"];

    check_missing_field(fog, "distance");
    check_missing_field(fog, "type");

    double distance = fog["distance"];
    std::string type = fog["type"];

    scene.set_fog(distance, type);
}

static void parse_ambient_light(const nlohmann::json& json, Scene& scene) {
    if (!has_field(json, "ambient_light"))
        return;

    scene.set_ambient_light(parse_color(json["ambient_light"]));
}

Scene SceneParser::parse() {
    auto json = parse_json_file(_path);

    /* Mandatory */
    check_missing_field(json, "camera");
    check_missing_field(json, "objects");
    check_missing_field(json, "lights");

    auto camera = parse_camera(json["camera"]);
    auto objects = parse_objects(json["objects"]);
    auto lights = parse_lights(json["lights"]);

    auto scene = Scene(camera);
    scene.set_objects(objects);
    scene.set_lights(lights);

    /* Optionals */
    parse_background_colors(json, scene);
    parse_fog(json, scene);
    parse_ambient_light(json, scene);

    return scene;
}

