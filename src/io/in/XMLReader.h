//
// Created by kimj2 on 05.06.2024.
//

#pragma once

#include "../../objects/ParticleContainer.h"
#include "FileReader.h"

namespace fileReaders {
    class XMLReader : public FileReader {
    public:
        XMLReader() = default;

        ~XMLReader() override = default;

        SimulationDataContainer readFile(const std::string &filepath) override;
    };
}// namespace fileReaders
