#pragma once

#include <filesystem>
#include <string>
#include <vector>

std::vector<std::string> listDir(const std::string& dir) {
    std::vector<std::string> files;

    for (const auto& input : fs::directory_iterator(dir)) {
        if (input.is_regular_file()) {
            files.push_back(input.path().string());
        }
    }

    return files;
}