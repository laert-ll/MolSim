#pragma once

#include "../../objects/ParticleContainer.h"
#include "input_schema.hxx"
#include "FileReader.h"
#include <string>
#include <vector>
#include <array>

namespace fileReaders {

    class XMLReader : public FileReader {
    public:
        SimulationDataContainer readFile(const std::string& filepath) override;
    private:
        void loadCuboids(const Simulation& simulation, ParticleContainer& particleContainer);

        FileWriterParameters loadFileWriterParameters(const Simulation &simulation);

        SimulationParameters loadSimulationParameters(const Simulation &simulation);

        ThermostatParameters loadThermostatParameters(const Simulation &simulation);

        BoundaryParameters loadBoundaryParameters(const Simulation &simulation);

        boundaries::BoundaryType stringToBoundaryType(const std::string &boundaryTypeStr);
    };

}  // namespace fileReaders
