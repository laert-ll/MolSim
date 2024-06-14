
#pragma once

#include "../../objects/ParticleContainer.h"
#include "io/in/parameters/CuboidParameters.h"
#include "ParticleGenerator.h"

namespace fileReaders {

    class FileReader {
    public:
        FileReader() = default;

        virtual ~FileReader() = default;

        static ParticleContainer readFile(const std::string& filepath);
    };
}// namespace fileReaders