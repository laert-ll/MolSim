//
// Created by kimj2 on 05.06.2024.
//

#pragma once

#include "../../../objects/ParticleContainer.h"
#include "FileWriterParameters.h"
#include "SimulationParameters.h"
#include "ThermostatParameters.h"
#include "BoundaryParameters.h"

#include <memory>

class SimulationDataContainer {
public:
    SimulationDataContainer(std::unique_ptr<ParticleContainer> particleContainer, std::unique_ptr<FileWriterParameters> fileWriterParameters,
                            std::unique_ptr<SimulationParameters> simulationParameters, std::unique_ptr<ThermostatParameters> thermostatParameters,
                            std::unique_ptr<BoundaryParameters> boundaryParameters)
            : particleContainer(std::move(particleContainer)), fileWriterParameters(std::move(fileWriterParameters)),
              simulationParameters(std::move(simulationParameters)), thermostatParameters(std::move(thermostatParameters)),
              boundaryParameters(std::move(boundaryParameters)){}

    [[nodiscard]] ParticleContainer* getParticleContainer() const {
        return particleContainer.get();
    }

    [[nodiscard]] FileWriterParameters* getFileWriterParameters() const {
        return fileWriterParameters.get();
    }

    [[nodiscard]] SimulationParameters* getSimulationParameters() const {
        return simulationParameters.get();
    }

    [[nodiscard]] ThermostatParameters* getThermostatParameters() const {
        return thermostatParameters.get();
    }

    [[nodiscard]] BoundaryParameters* getBoundaryParameters() const {
        return boundaryParameters.get();
    }

private:
    std::unique_ptr<ParticleContainer> particleContainer;
    std::unique_ptr<FileWriterParameters> fileWriterParameters;
    std::unique_ptr<SimulationParameters> simulationParameters;
    std::unique_ptr<ThermostatParameters> thermostatParameters;
    std::unique_ptr<BoundaryParameters> boundaryParameters;
};