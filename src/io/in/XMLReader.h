#pragma once

#include "../../objects/ParticleContainer.h"
#include <string>

class XMLReader {
public:
    static ParticleContainer readFile(const std::string& filepath);
};
