//
// Created by kimj2 on 11.06.2024.
//

#pragma once

#include "../objects/ParticleContainer.h"
#include "Thermostat.h"
#include "../utils/ArrayUtils.h"
#include "../utils/MaxwellBoltzmannDistribution.h"


void Thermostat::initializeTemp(ParticleContainer &particleContainer) const {
    if (particleContainer.hasZeroVelocities()) { // Check if all velocities are zero
        // Initialize velocities by applying Brownian motion
        double maxwellBoltzmannFactor;

        for (auto &particle : particleContainer.getParticles()) {
            maxwellBoltzmannFactor = sqrt(start_temp / particle.getM());

            std::array<double, 3> v = particle.getV();
            const std::array<double, 3> deltaV = maxwellBoltzmannDistributedVelocity(maxwellBoltzmannFactor, 3);

            for (int i = 0; i < dimension; ++i) {
                v[i] += deltaV[i];
            }

            particle.setV(v);
        }
    }

    // Velocity scaling to initial temperature
    setTemp(particleContainer, start_temp);
}

void Thermostat::setTempDirectly(ParticleContainer &particleContainer) const {
    setTemp(particleContainer, target_temp);
}

void Thermostat::setTempGradually(ParticleContainer &particleContainer) const {
    const double currentTemp = calculateCurrentTemp(particleContainer);
    const double delta_temp = std::max(std::abs(target_temp - currentTemp), this->max_delta_temp);
    const double updatedTemp = this->target_temp > currentTemp ? currentTemp + delta_temp : currentTemp - delta_temp;
    setTemp(particleContainer, updatedTemp);
}


//----------------------------------------Helper functions----------------------------------------------------

double Thermostat::calculateCurrentTemp(ParticleContainer &particleContainer) const {
    double kinEnergy = calculateKinEnergy(particleContainer);
    return 2.0 / (this->dimension * particleContainer.getSize()) * kinEnergy;
}

double Thermostat::calculateKinEnergy(ParticleContainer &particleContainer) const {
    double kinEnergy = 0.0;
    for (auto &particle : particleContainer.getParticles()) {
        kinEnergy += 0.5 * particle.getM() * ArrayUtils::dotProduct(particle.getV(), particle.getV());
    }
    return kinEnergy;
}

void Thermostat::scaleV(double beta, ParticleContainer &particleContainer) const {
    for (auto particle : particleContainer.getParticles()) {
        std::array<double, 3> v = particle.getV();
        v = beta * v;
        particle.setV(v);
    }
}

void Thermostat::setTemp(ParticleContainer &particleContainer, double newTemp) const {
    const double currentTemp = calculateCurrentTemp(particleContainer);
    const double beta = sqrt(newTemp / currentTemp);
    scaleV(beta, particleContainer);
}
