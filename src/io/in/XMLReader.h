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

        static FileWriterParameters loadFileWriterParameters(const Simulation &simulation);

        static SimulationParameters loadSimulationParameters(const Simulation &simulation);

        static ThermostatParameters loadThermostatParameters(const Simulation &simulation);

        static BoundaryParameters loadBoundaryParameters(const Simulation &simulation);

        static boundaries::BoundaryType stringToBoundaryType(const std::string &boundaryTypeStr);
    };

}  // namespace fileReaders
