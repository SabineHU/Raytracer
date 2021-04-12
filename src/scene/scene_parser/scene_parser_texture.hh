#pragma once

#include <iostream>

#include "json.hpp"
#include "scene_parser_utils.hh"
#include "perlin_noise.hh"
#include "lambertian.hh"
#include "metal.hh"
#include "image_texture.hh"
#include "checkerboard.hh"
#include "strip.hh"

inline shared_texture parse_texture(const nlohmann::json& json);

static shared_texture parse_lambertian_texture(const nlohmann::json& json) {
    check_missing_field(json, "color");

    Color color = parse_color(json["color"]);
    return std::make_shared<Lambertian>(color);
}

static shared_texture parse_metal_texture(const nlohmann::json& json) {
    check_missing_field(json, "color");

    Color color = parse_color(json["color"]);
    return std::make_shared<Metal>(color);
}

static shared_texture parse_image_texture(const nlohmann::json& json) {
    check_missing_field(json, "asset");

    const std::string& asset = json["asset"];
    auto image = std::make_shared<ImageTexture>(asset);

    if (has_field(json, "is_reverted")) {
        bool is_reverted = json["is_reverted"];
        if (is_reverted)
            image->reverse_image();
    }

    return image;
}

static PerlinNoiseType parse_perlin_noise_type(const nlohmann::json& json) {
    if (json == "cloud") return CLOUD;
    if (json == "marble") return MARBLE;
    if (json == "noise") return NOISE;
    if (json == "rainbow") return RAINBOW;
    if (json == "turbulence") return TURBULENCE;
    if (json == "wood") return WOOD;

    std::cerr << "Unsupported noise type \"" << json << "\"!" << std::endl;
    exit(1);
}

static shared_texture parse_perlin_noise_texture(const nlohmann::json& json) {
    check_missing_field(json, "scale");
    check_missing_field(json, "type");
    check_missing_field(json, "color1");
    check_missing_field(json, "color2");

    double scale = json["scale"];
    auto perlin_type = parse_perlin_noise_type(json["type"]);
    auto color1 = parse_color(json["color1"]);
    auto color2 = parse_color(json["color2"]);

    return std::make_shared<PerlinNoise>(scale, perlin_type, color1, color2);
}

static void parse_texture_coeffs(const nlohmann::json& json, shared_texture texture) {
    if (has_field(json, "ka")) {
        double ka = json["ka"];
        texture->ka = ka;
    }

    if (has_field(json, "kd")) {
        double kd = json["kd"];
        texture->kd = kd;
    }

    if (has_field(json, "ks")) {
        double ks = json["ks"];
        texture->ks = ks;
    }

    if (has_field(json, "kt")) {
        double kt = json["kt"];
        texture->ks = kt;
    }
}

static void parse_texture_type(const nlohmann::json& json, shared_texture texture) {
    // TODO: @sebmenozzi should allow multiple types

    if (has_field(json, "is_reflected")) {
        bool is_reflected = json["is_reflected"];

        if (is_reflected)
            texture->set_reflection_type();
    }

    if (has_field(json, "is_refracted")) {
        bool is_refracted = json["is_refracted"];

        if (is_refracted)
            texture->set_refraction_type();
    }

    if (has_field(json, "is_transparent")) {
        bool is_transparent = json["is_transparent"];

        if (is_transparent)
            texture->set_transparent_type();
    }
}

static shared_texture parse_checkerboard_texture(const nlohmann::json& json) {
    auto checkerboard_type = json["type"];

    if (checkerboard_type == "color") {
        check_missing_field(json, "color1");
        check_missing_field(json, "color2");

        Color color1 = parse_color(json["color1"]);
        Color color2 = parse_color(json["color2"]);

        auto texture = std::make_shared<CheckerBoard>(color1, color2);

        if (has_field(json, "scale")) {
            double scale = json["scale"];
            texture->set_scale(scale);
        }
        return texture;

    } else if (checkerboard_type == "texture") {
        check_missing_field(json, "texture1");
        check_missing_field(json, "texture2");

        auto texture1 = parse_texture(json["texture1"]);
        auto texture2 = parse_texture(json["texture2"]);

        return std::make_shared<CheckerBoard>(texture1, texture2);
    }

    std::cerr << "Unsupported checkerboard type \"" << checkerboard_type << "\"!\n";
    exit(1);
}

static shared_texture parse_strip_texture(const nlohmann::json& json) {
    check_missing_field(json, "color1");
    check_missing_field(json, "color2");

    auto color1 = parse_color(json["color1"]);
    auto color2 = parse_color(json["color2"]);

    auto texture = std::make_shared<Strip>(color1, color2);

    if (has_field(json, "is_planar")) {
        bool is_planar = json["is_planar"];
        texture->set_planar(is_planar);
    }

    if (has_field(json, "is_horizontal")) {
        bool is_horizontal = json["is_horizontal"];
        texture->set_horizontal(is_horizontal);
    }

    if (has_field(json, "scale")) {
        double scale = json["scale"];
        texture->set_scale(scale);
    }

    if (has_field(json, "scale")) {
        double scale = json["scale"];
        texture->set_scale(scale);
    }

    return texture;
}

inline shared_texture parse_texture(const nlohmann::json& json) {
    auto texture_type = json["type"];

    shared_texture texture;

    if (texture_type == "lambertian") {
        texture = parse_lambertian_texture(json);
    } else if (texture_type == "perlin_noise") {
        check_missing_field(json, "perlin_noise");
        texture = parse_perlin_noise_texture(json["perlin_noise"]);
    } else if (texture_type == "metal") {
        texture = parse_metal_texture(json);
    } else if (texture_type == "image") {
        check_missing_field(json, "image");
        texture = parse_image_texture(json["image"]);
    } else if (texture_type == "checkerboard") {
        check_missing_field(json, "checkerboard");
        texture = parse_checkerboard_texture(json["checkerboard"]);
    } else if (texture_type == "strip") {
        check_missing_field(json, "strip");
        texture = parse_strip_texture(json["strip"]);
    } else {
        std::cerr << "Unsupported texture type \"" << texture_type << "\"!" << std::endl;
        exit(1);
    }

    parse_texture_coeffs(json, texture);
    parse_texture_type(json, texture);

    return texture;
}

static Noise parse_noise(const nlohmann::json& json) {
    check_missing_field(json, "type");
    check_missing_field(json, "scale");

    auto perlin_type = parse_perlin_noise_type(json["type"]);
    double scale = json["scale"];

    return Noise(perlin_type, scale);
}

static void parse_bump_mapping(const nlohmann::json& json, shared_object object) {
    check_missing_field(json, "noise");

    auto noise = parse_noise(json["noise"]);

    if (has_field(json, "coeff")) {
        double coeff = json["coeff"];
        object->add_bump_mapping(noise, coeff);
    } else
        object->add_bump_mapping(noise);
}

static void parse_bump_mappings(const nlohmann::json& json, shared_object object) {
    for (const auto& bump_mapping : json)
        parse_bump_mapping(bump_mapping, object);
}
