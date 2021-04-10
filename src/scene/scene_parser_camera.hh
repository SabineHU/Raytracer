#pragma once

#include "json.hpp"
#include "scene_parser_utils.hh"
#include "camera.hh"

Camera parse_camera(const nlohmann::json& json)
{
    check_missing_field(json, "look_from");
    check_missing_field(json, "look_at");
    check_missing_field(json, "vup");

    Vect look_from = parse_vect(json["look_from"]);
    Vect look_at = parse_vect(json["look_at"]);
    Vect vup = parse_vect(json["vup"]);

    return Camera(look_from, look_at, vup);
}
