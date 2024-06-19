//
// Created by kimj2 on 11.06.2024.
//

#pragma once

#include "../objects/ParticleContainer.h"
#include "objects/LinkedCellContainer.h"

class Thermostat {
public:
    Thermostat() = default;

    Thermostat(double start_temp, double target_temp, int applyFrequency, double max_delta_temp,
               int dimension) :
            start_temp(start_temp), target_temp(target_temp), applyFrequency(applyFrequency),
            max_delta_temp(max_delta_temp), dimension(dimension) {}

    void setTempDirectly(ParticleContainer &particleContainer) const;
    void setTempDirectly(LinkedCellContainer &linkedCellContainer) const;

    void setTempGradually(ParticleContainer &particleContainer) const;
    void setTempGradually(LinkedCellContainer &linkedCellContainer) const;

    void initializeTemp(ParticleContainer &particleContainer) const;
    void initializeTemp(LinkedCellContainer &linkedCellContainer) const;

    double calculateCurrentTemp(ParticleContainer &particleContainer) const;
    double calculateCurrentTemp(LinkedCellContainer &linkedCellContainer) const;

    [[nodiscard]] double getStartTemp() const {
        return start_temp;
    }

    [[nodiscard]] double getTargetTemp() const {
        return target_temp;
    }

    [[nodiscard]] int getApplyFrequency() const {
        return applyFrequency;
    }

    [[nodiscard]] double getMaxDeltaTemp() const {
        return max_delta_temp;
    }

    [[nodiscard]] int getDimension() const {
        return dimension;
    }

private:
    double start_temp;
    double target_temp;
    int applyFrequency;
    double max_delta_temp;
    int dimension;

    double calculateKinEnergy(ParticleContainer &particleContainer) const;
    double calculateKinEnergy(LinkedCellContainer &linkedCellContainer) const;

    void scaleV(double beta, ParticleContainer &particleContainer) const;
    void scaleV(double beta, LinkedCellContainer &linkedCellContainer) const;

    void setTemp(ParticleContainer &particleContainer, double newTemp) const;
    void setTemp(LinkedCellContainer &linkedCellContainer, double newTemp) const;
};