#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

namespace CSVManipulation {
    class ReadFile {
    private:
        std::string path;
        std::vector<std::vector<std::string>> contentCSV;

    public:
        ReadFile(std::string filePath) {
            this->path = filePath;
        }

        int read() {
            std::ifstream arq(this->path);

            if (!arq.is_open()) {
                std::cerr << "ERROR! File is Not Open!\n";
                return 1;
            }

            std::vector<std::vector<std::string>> dados;

            std::string linha;
            while (std::getline(arq, linha)) {
                std::vector<std::string> linha_dados;
                std::istringstream linha_stream(linha);
                std::string campo;

                while(std::getline(linha_stream, campo, ',')) {
                    linha_dados.push_back(campo);
                }

                dados.push_back(linha_dados);
            }
            
            arq.close();

            this->contentCSV = dados;

            return 0;
        }

        std::vector<std::vector<std::string>> getValueCSV() {
            return this->contentCSV;
        }
    };

    class WriteFile {
    private:
        std::string path;
        std::vector<std::vector<std::string>> content;

    public:
        WriteFile(std::string path, std::vector<std::vector<std::string>> content) {
            this->path = path;
            this->content = content;
        }

        int write() {
            std::ofstream nFile(this->path);

            if (!nFile.is_open()) {
                std::cerr << "ERROR! File is Not Open!\n";
                return 1;
            }

            for (int i = 0; i < this->content.size(); i++) {
                for (int x = 0; x < this->content[i].size(); x++) {
                    nFile << this->content[i][x] << ',';
                }
                nFile << '\n';
            }

            nFile.close();
            return 0;
        }
    };
}
