//
// Created by kimj2 on 05.06.2024.
//

#pragma once

#include "../../../objects/ParticleContainer.h"
#include "FileWriterParameters.h"
#include "SimulationParameters.h"
#include "ThermostatParameters.h"
#include "BoundaryParameters.h"
#include "LinkedCellsParameters.h"

#include <memory>

class SimulationDataContainer {
public:
    SimulationDataContainer(std::unique_ptr<ParticleContainer> particleContainer,
                            std::unique_ptr<LinkedCellContainer> linkedCellContainer,
                            std::unique_ptr<FileWriterParameters> fileWriterParameters,
                            std::unique_ptr<SimulationParameters> simulationParameters,
                            std::unique_ptr<ThermostatParameters> thermostatParameters,
                            std::unique_ptr<LinkedCellsParameters> linkedCellsParameters,
                            std::unique_ptr<BoundaryParameters> boundaryParameters)
            : particleContainer(std::move(particleContainer)),
              linkedCellContainer(std::move(linkedCellContainer)),
              fileWriterParameters(std::move(fileWriterParameters)),
              simulationParameters(std::move(simulationParameters)),
              thermostatParameters(std::move(thermostatParameters)),
              linkedCellsParameters(std::move(linkedCellsParameters)),
              boundaryParameters(std::move(boundaryParameters)) {}

    [[nodiscard]] ParticleContainer *getParticleContainer() const {
        return particleContainer.get();
    }

    [[nodiscard]] LinkedCellContainer *getLinkedCellContainer() const {
        return linkedCellContainer.get();
    }

    [[nodiscard]] FileWriterParameters *getFileWriterParameters() const {
        return fileWriterParameters.get();
    }

    [[nodiscard]] SimulationParameters *getSimulationParameters() const {
        return simulationParameters.get();
    }

    [[nodiscard]] ThermostatParameters *getThermostatParameters() const {
        return thermostatParameters.get();
    }

    [[nodiscard]] LinkedCellsParameters *getLinkedCellsParameters() const {
        return linkedCellsParameters.get();
    }

    [[nodiscard]] BoundaryParameters *getBoundaryParameters() const {
        return boundaryParameters.get();
    }

private:
    std::unique_ptr<ParticleContainer> particleContainer;
    std::unique_ptr<LinkedCellContainer> linkedCellContainer;
    std::unique_ptr<FileWriterParameters> fileWriterParameters;
    std::unique_ptr<SimulationParameters> simulationParameters;
    std::unique_ptr<ThermostatParameters> thermostatParameters;
    std::unique_ptr<LinkedCellsParameters> linkedCellsParameters;
    std::unique_ptr<BoundaryParameters> boundaryParameters;
};