#pragma once

#include <fstream>
#include <iostream>

namespace file {

inline std::ifstream open_file(const std::string& path) {
    std::ifstream file(path.c_str());

    if (!file.is_open())
    {
        std::cerr << "Could not open scene file!\n";
        exit(1);
    }

    return file;
}

}
