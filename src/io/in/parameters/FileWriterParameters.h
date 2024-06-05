//
// Created by kimj2 on 05.06.2024.
//

#pragma once

#include <string>
#include <utility>

class FileWriterParameters {
public:
    FileWriterParameters() : baseName(""), writeFrequency(-1) {} // default constructor

    FileWriterParameters(std::string baseName, int outputWriteFrequency)
            : baseName(std::move(baseName)), writeFrequency(outputWriteFrequency) {}


    [[nodiscard]] const std::string &getBaseName() const {
        return baseName;
    }

    [[nodiscard]] int getOutputWriteFrequency() const {
        return writeFrequency;
    }
private:
    const std::string baseName;
    const int writeFrequency; // How often to write output (every n-th step)
};