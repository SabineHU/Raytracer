#pragma once

#include <fstream>
#include <iostream>

namespace file {

inline std::ifstream open_file(const std::string& path) {
    std::ifstream file(path.c_str());

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << path << std::endl;
        exit(1);
    }

    return file;
}

inline std::ofstream open_writing_file(const std::string& path) {
    std::ofstream file(path.c_str());

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << path << std::endl;
        exit(1);
    }

    return file;
}

}
