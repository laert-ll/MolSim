#pragma once

#include "../../objects/ParticleContainer.h"
#include "FileReader.h"
#include <string>

namespace fileReaders {
    class XMLReader : public FileReader {
    public:
        XMLReader() = default;

        ~XMLReader() override = default;

        static ParticleContainer readFile(const std::string& filepath);
    };
}// namespace fileReaders