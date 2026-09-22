#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "csvmanipull.hpp"

std::vector<std::string> listDir(const std::string& dir) {
    std::vector<std::string> files;

    for (const auto& input : std::filesystem::directory_iterator(dir)) {

        if (input.is_regular_file()) {

            files.push_back(input.path().stem().string());

        }
        
    }

    return files;
}

int exec_appimage(std::string appimage_name) {
    CSVManipulation::ReadFile config_file("./settings.csv");

    if (config_file.read() != 0) return 1;

    for (int x = 0; x < config_file.getValueCSV().size(); x++) {

        if (appimage_name == config_file.getValueCSV()[x][0]) {

            system(config_file.getValueCSV()[x][1].c_str());
            return 0;

        }

    }

    return 1;
}
