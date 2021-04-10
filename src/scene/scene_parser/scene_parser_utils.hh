#pragma once

#include <iostream>
#include <string>

#include "random.hh"
#include "color.hh"

static bool has_field(const nlohmann::json& json, const std::string& field) {
    auto it = json.find(field);
    return it != json.end();
}

static void check_missing_field(const nlohmann::json& json, const std::string& field) {
    if (!has_field(json, field)) {
        std::cerr << "Bad scene file: missing \"" << field << "\"!\n";
        exit(1);
    }
}

inline Vect parse_vect(const nlohmann::json& json) {
    if (json == "random") return r_random::random_vector();

    check_missing_field(json, "x");
    check_missing_field(json, "y");
    check_missing_field(json, "z");

    double x = json["x"];
    double y = json["y"];
    double z = json["z"];

    return Vect(x, y, z);
}

inline Color parse_color(const nlohmann::json& json) {
    // TODO: @sebmenozzi refacto, make the colors detection automatic from color.hh...
    if (json == "random") return r_random::random_color();
    if (json == "random_pastel") return r_random::random_pastel_color();
    if (json == "white") return white;
    if (json == "black") return black;
    if (json == "light_red") return light_red;
    if (json == "red") return red;
    if (json == "dark_red") return dark_red;
    if (json == "orange") return orange;
    if (json == "light_orange") return light_orange;
    if (json == "yellow") return yellow;
    if (json == "light_green") return light_green;
    if (json == "green") return green;
    if (json == "green2") return green2;
    if (json == "turquoise") return turquoise;
    if (json == "light_blue") return light_blue;
    if (json == "blue") return blue;
    if (json == "blue2") return blue2;
    if (json == "blue3") return blue3;
    if (json == "dark_blue") return dark_blue;
    if (json == "light_purple") return light_purple;
    if (json == "purple") return purple;
    if (json == "dark_purple") return dark_purple;
    if (json == "light_pink") return light_pink;
    if (json == "pink") return pink;
    if (json == "dark_pink") return dark_pink;

    check_missing_field(json, "r");
    check_missing_field(json, "g");
    check_missing_field(json, "b");

    double r = json["r"];
    double g = json["g"];
    double b = json["b"];

    return Color(r, g, b);
}
