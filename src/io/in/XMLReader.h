#pragma once

#include "../../objects/ParticleContainer.h"
#include "input_schema.hxx"
#include "FileReader.h"
#include <string>


namespace fileReaders {

    class XMLReader {
    public:
        static SimulationDataContainer readFile(const std::string& filepath);
    private:
        static void loadCuboids(const Simulation& simulation, ParticleContainer& particleContainer);
    };

}  // namespace fileReaders
