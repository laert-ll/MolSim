//
// Created by kimj2 on 07.05.2024.
//
#include "ParticleGenerator.h"
#include "../../utils/MaxwellBoltzmannDistribution.h"
#include "../../utils/ArrayUtils.h"
#include "spdlog/spdlog.h"

Particle ParticleGenerator::generateParticle(const ParticleParameters &parameters) {
    std::array<double, 3> x = parameters.getPosition();
    std::array<double, 3> v = parameters.getVelocity();
    double m = parameters.getMass();
    double volume = parameters.getVolume();
    int type = parameters.getType();
    SPDLOG_DEBUG("Generated particle: [Position: [{}, {}, {}], Velocity: [{}, {}, {}], Mass: {}, Volume: {}, Type: {}]",
                 x[0], x[1], x[2], v[0], v[1], v[2], m, volume, type);
    return {parameters.getPosition(),
                    parameters.getVelocity(),
                    parameters.getMass(),
                    parameters.getVolume(),
                    parameters.getType()};
}

void ParticleGenerator::generateCuboid(const CuboidParameters &parameters, ParticleContainer& particleContainer) {
    // Extract parameters for easier access
    const auto &lowerLeftFrontCorner = parameters.lowerLeftFrontCorner;
    const auto &numParticlesPerDimension = parameters.numParticlesPerDimension;
    const auto &distance = parameters.distance;
    const auto &m = parameters.m;
    const auto &startV = parameters.startV;
    const auto &meanV = parameters.meanV;
    SPDLOG_DEBUG("Generating cuboid: LLF [{} {} {}], NumParticles [{} {} {}], Distance {}, Mass {}, StartV [{} {} {}], MeanV {}",
                 lowerLeftFrontCorner[0], lowerLeftFrontCorner[1], lowerLeftFrontCorner[2], numParticlesPerDimension[0], numParticlesPerDimension[1],
                 numParticlesPerDimension[2], distance, m, startV[0], startV[1], startV[2], meanV);

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
                const std::array<double, 3> deltaV = maxwellBoltzmannDistributedVelocity(meanV, 2);

                // Add deltaV to v
                const std::array<double, 3> v = ArrayUtils::elementWisePairOp(startV, deltaV, std::plus<>());

                // Create a new particle and add it to the container
                Particle newParticle(x, v, m, 0, 0); // Set volume and type to zero for now
                particleContainer.addParticle(newParticle);
            }
        }
    }
}
