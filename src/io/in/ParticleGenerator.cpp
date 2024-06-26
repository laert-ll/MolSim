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
    SPDLOG_DEBUG("Generated particle: x {}, v {}, mass {}, volume {}, type {}",
                 ArrayUtils::to_string(x), ArrayUtils::to_string(v), m, volume, type);
    return {parameters.getPosition(),
            parameters.getVelocity(),
            parameters.getMass(),
            parameters.getVolume(),
            parameters.getType()};
}

void ParticleGenerator::generateCuboid(const CuboidParameters &parameters, ParticleContainer &particleContainer) {
    // Extract parameters for easier access
    const auto &lowerLeftFrontCorner = parameters.getLowerLeftFrontCorner();
    const auto &numParticlesPerDimension = parameters.getNumParticlesPerDimension();
    const auto &distance = parameters.getDistance();
    const auto &m = parameters.getMass();
    const auto &startV = parameters.getStartV();
    const auto &meanV = parameters.getMeanV();
    const auto &dimension = parameters.getDimension();
    SPDLOG_DEBUG("Generating cuboid: LLF {}, NumParticles {}, Distance {}, Mass {}, StartV {}, MeanV {}",
                 ArrayUtils::to_string(lowerLeftFrontCorner), ArrayUtils::to_string(numParticlesPerDimension), distance,
                 m, ArrayUtils::to_string(startV), meanV);
    int i = 0;
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

                std::array<double, 3> v = startV;
                // Add elements of deltaV to v based on dimension
                for (int i = 0; i < dimension; ++i) {
                    v[i] += deltaV[i];
                }
                // Create a new particle and add it to the container
                Particle newParticle(x, v, m, 0, 0); // Set volume and type to zero for now
                i++;
                particleContainer.addParticle(newParticle);
                particleContainer.reassign(newParticle);
            }
        }
    }
}

void ParticleGenerator::generateDisc(const DiscParameters &parameters, ParticleContainer &particleContainer) {
    // Extract parameters for easier access
    const auto &center = parameters.getCenter();
    const auto &startV = parameters.getStartV();
    const int numParticlesAlongRadius = parameters.getNumParticlesAlongRadius();
    const double distance = parameters.getDistance();
    const double mass = parameters.getMass();

    SPDLOG_DEBUG("Generating disc: Center {}, startV {}, numParticlesAlongRadius {}, Distance {}",
                 ArrayUtils::to_string(center), ArrayUtils::to_string(startV), numParticlesAlongRadius, distance);

    // Generate particles for the disc
    for (int i = -numParticlesAlongRadius; i <= numParticlesAlongRadius; ++i) {
        for (int j = -numParticlesAlongRadius; j <= numParticlesAlongRadius; ++j) {
            if (i * i + j * j <=
                numParticlesAlongRadius * numParticlesAlongRadius) { // Check if the position is inside the disc
                // Calculate the position of the particle
                const std::array<double, 3> x = {
                        center[0] + i * distance,
                        center[1] + j * distance,
                        center[2]
                };

                // Create a new particle and add it to the container
                Particle newParticle(x, startV, mass, 0, 0);
                particleContainer.addParticle(newParticle);
            }
        }
    }
}