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

int copy_appimage(std::string appimage_name, std::string appimage_path) {
    try {
        std::vector<std::vector<std::string>> conf_csv;
        std::vector<std::string> new_conf;
        std::filesystem::path appimage_original_path = appimage_path;
        std::string destiny_path = "./appimages/" + appimage_original_path.filename().string();
        std::filesystem::copy_file(appimage_path, destiny_path, std::filesystem::copy_options::overwrite_existing);

        CSVManipulation::ReadFile conf_file("./settings.csv");

        if (conf_file.read() != 0) return 1;

        conf_csv = conf_file.getValueCSV();

        new_conf.push_back(appimage_name);
        new_conf.push_back(destiny_path);

        conf_csv.push_back(new_conf);

        CSVManipulation::WriteFile new_conf_file("./settings.csv", conf_csv);

        if (new_conf_file.write() != 0) return 1;


        return 0;

    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "ERROR! : " << e.what() << std::endl;
        return 1;

    }
}
