
#pragma once

#include "../../objects/ParticleContainer.h"
#include "io/in/parameters/CuboidParameters.h"
#include "ParticleGenerator.h"
#include "io/in/parameters/SimulationDataContainer.h"

namespace fileReaders {

    class FileReader {
    public:
        FileReader() = default;

        virtual ~FileReader() = default;

        virtual SimulationDataContainer readFile(const std::string& filePath) = 0;
    };
}// namespace fileReaders