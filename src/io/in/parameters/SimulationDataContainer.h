//
// Created by kimj2 on 05.06.2024.
//

#pragma once

#include "../../../objects/ParticleContainer.h"
#include "FileWriterParameters.h"
#include "SimulationParameters.h"

class SimulationDataContainer {
public:
    SimulationDataContainer(ParticleContainer &particleContainer, FileWriterParameters &fileWriterParameters,
                            SimulationParameters &simulationParameters)
            : particleContainer(particleContainer), fileWriterParameters(fileWriterParameters),
              simulationParameters(simulationParameters) {}

    [[nodiscard]] ParticleContainer &getParticleContainer() const {
        return particleContainer;
    }

    [[nodiscard]] FileWriterParameters &getFileWriterParameters() const {
        return fileWriterParameters;
    }

    [[nodiscard]] SimulationParameters &getSimulationParameters() const {
        return simulationParameters;
    }


private:
    ParticleContainer &particleContainer;
    FileWriterParameters &fileWriterParameters;
    SimulationParameters &simulationParameters;

};