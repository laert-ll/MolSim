//
// Created by kimj2 on 07.05.2024.
//
#include "ParticleGenerator.h"
#include "../../utils/MaxwellBoltzmannDistribution.h"
#include "../../utils/ArrayUtils.h"

Particle ParticleGenerator::generateParticle(const ParticleParameters &parameters) {
    return Particle(parameters.getPosition(),
                    parameters.getVelocity(),
                    parameters.getMass(),
                    parameters.getVolume(),
                    parameters.getType());
}

void ParticleGenerator::generateCuboid(const CuboidParameters &parameters, ParticleContainer& particleContainer) {
    // Extract parameters for easier access
    const auto &lowerLeftFrontCorner = parameters.lowerLeftFrontCorner;
    const auto &numParticlesPerDimension = parameters.numParticlesPerDimension;
    const auto &distance = parameters.distance;
    const auto &m = parameters.m;
    const auto &startV = parameters.startV;
    const auto &meanV = parameters.meanV;

    // Generate particles for the cuboid
    for (std::size_t xIndex = 0; xIndex < numParticlesPerDimension[0]; ++xIndex) {
        for (std::size_t yIndex = 0; yIndex < numParticlesPerDimension[1]; ++yIndex) {
            for (std::size_t zIndex = 0; zIndex < numParticlesPerDimension[2]; ++zIndex) {
                // Calculate the position of the particle
                const std::array<double, 3> x = {
                        lowerLeftFrontCorner[0] + xIndex * distance,
                        lowerLeftFrontCorner[1] + yIndex * distance,
                        lowerLeftFrontCorner[2] + zIndex * distance
                };

                // Simulate Brownian Motion by using MaxwellBoltzmannDistribution
                const std::array<double, 3> deltaV = maxwellBoltzmannDistributedVelocity(meanV, 3);

                // Add deltaV to v
                const std::array<double, 3> v = ArrayUtils::elementWisePairOp(startV, deltaV, std::plus<double>());

                // Create a new particle and add it to the container
                Particle newParticle(x, v, m, 0, 0); // Set volume and type to zero for now
                particleContainer.addParticle(newParticle);
            }
        }
    }
}
