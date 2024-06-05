//
// Created by kimj2 on 05.06.2024.
//

#pragma once

#include <string>
#include <utility>

class FileWriterParameters {
public:
    FileWriterParameters() : baseName(""), outputWriteFrequency(-1) {} // default constructor

    FileWriterParameters(std::string baseName, int outputWriteFrequency)
            : baseName(std::move(baseName)), outputWriteFrequency(outputWriteFrequency) {}


    [[nodiscard]] const std::string &getBaseName() const {
        return baseName;
    }

    [[nodiscard]] int getOutputWriteFrequency() const {
        return outputWriteFrequency;
    }
private:
    const std::string baseName;
    const int outputWriteFrequency; // How often to write output (every n-th step)
};