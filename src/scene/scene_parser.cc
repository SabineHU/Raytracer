#include <memory>

#include "scene_parser.hh"
#include "json.hpp"
#include "file.hh"
#include "scene_parser_utils.hh"
#include "scene_parser_camera.hh"
#include "scene_parser_objects.hh"
#include "scene_parser_lights.hh"

SceneParser::SceneParser(const std::string& path): _path(path) {}

Scene SceneParser::parse() {
    auto file = file::open_file(_path);
    auto json = nlohmann::json::parse(file);

    check_missing_field(json, "camera");
    auto camera = parse_camera(json["camera"]);

    check_missing_field(json, "objects");
    auto objects = parse_objects(json["objects"]);

    Color ambient_light;
    if (has_field(json, "ambient_light"))
        ambient_light = parse_color(json["ambient_light"]);

    check_missing_field(json, "lights");
    auto lights = parse_lights(json["lights"]);

    file.close();

    auto scene = Scene(camera);
    scene.set_ambient_light(ambient_light);
    scene.set_objects(objects);
    scene.set_lights(lights);

    if (has_field(json, "backgrounds_colors"))
    {
        auto backgrounds_colors = json["backgrounds_colors"];

        check_missing_field(backgrounds_colors, "color1");
        check_missing_field(backgrounds_colors, "color2");

        auto color1 = parse_color(backgrounds_colors["color1"]);
        auto color2 = parse_color(backgrounds_colors["color2"]);

        scene.set_background_colors(color1, color2);
    }

    if (has_field(json, "fog"))
    {
        auto fog = json["fog"];

        check_missing_field(fog, "distance");
        check_missing_field(fog, "type");

        double distance = fog["distance"];
        std::string type = fog["type"];

        scene.set_fog(distance, type);
    }

    return scene;
}
