//
// Created by kimj2 on 05.06.2024.
//

#pragma once

#include <string>
#include <utility>

class FileWriterParameters {
public:
    FileWriterParameters() : baseName(""), writeFrequency(-1) {} // default constructor

    FileWriterParameters(std::string baseName, int writeFrequency)
            : baseName(std::move(baseName)), writeFrequency(writeFrequency) {}


    const std::string &getBaseName() const {
        return baseName;
    }

    int getWriteFrequency() const {
        return writeFrequency;
    }
private:
    const std::string baseName;
    const int writeFrequency; // How often to write output (every n-th step)
};