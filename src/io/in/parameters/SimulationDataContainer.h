//
// Created by kimj2 on 05.06.2024.
//

#pragma once

#include "../../../objects/ParticleContainer.h"
#include "FileWriterParameters.h"
#include "SimulationParameters.h"
#include "ThermostatParameters.h"

class SimulationDataContainer {
public:
    SimulationDataContainer(ParticleContainer &particleContainer, FileWriterParameters &fileWriterParameters,
                            SimulationParameters &simulationParameters, ThermostatParameters &thermostatParameters)
            : particleContainer(particleContainer), fileWriterParameters(fileWriterParameters),
              simulationParameters(simulationParameters), thermostatParameters(thermostatParameters) {}

    [[nodiscard]] ParticleContainer &getParticleContainer() const {
        return particleContainer;
    }

    [[nodiscard]] FileWriterParameters &getFileWriterParameters() const {
        return fileWriterParameters;
    }

    [[nodiscard]] SimulationParameters &getSimulationParameters() const {
        return simulationParameters;
    }

    [[nodiscard]] ThermostatParameters &getThermostatParameters() const {
        return thermostatParameters;
    }

private:
    ParticleContainer &particleContainer;
    FileWriterParameters &fileWriterParameters;
    SimulationParameters &simulationParameters;
    ThermostatParameters &thermostatParameters;

};