#pragma once

#include <vector>

#include "json.hpp"
#include "scene_parser_utils.hh"
#include "point_light.hh"

static shared_light parse_light(const nlohmann::json& light) {
    check_missing_field(light, "position");
    check_missing_field(light, "color");
    check_missing_field(light, "intensity");

    Point3 position = parse_vect(light["position"]);
    Color color = parse_color(light["color"]);
    double intensity = light["intensity"];

    return std::make_shared<PointLight>(PointLight(position, color, intensity));
}

inline std::vector<shared_light> parse_lights(const nlohmann::json& json) {
    std::vector<shared_light> lights;

    for (auto light : json)
        lights.push_back(parse_light(light));

    return lights;
}
