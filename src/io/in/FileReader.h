
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

        static SimulationDataContainer readFile(const std::string& filepath);
    };
}// namespace fileReaders