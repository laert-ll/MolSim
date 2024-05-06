//
// Created by kimj2 on 07.05.2024.
//

#include <array>

/**
 * @struct CuboidParameters
 * @brief Structure to hold the parameters for a cuboid in the simulation.
 */
struct CuboidParameters {
    /**
     * @brief Coordinate of the lower left front-side corner of the cuboid.
     */
    std::array<double, 3> lowerLeftFrontCorner;

    /**
     * @brief Number of particles in each dimension of the cuboid.
     */
    std::array<std::size_t, 3> numParticlesPerDimension;

    /**
     * @brief Distance between particles (mesh width of the grid).
     */
    double particleDistance;

    /**
     * @brief Mass of one particle.
     */
    double particleMass;

    /**
     * @brief Initial velocity of the particles in each dimension.
     */
    std::array<double, 3> initialVelocity;

    /**
     * @brief Mean-value of the velocity of the Brownian Motion.
     */
    double meanVelocity;

    /**
     * @brief Temperature for the Maxwell-Boltzmann distribution.
     */
    double temperature;

    /**
     * @brief Constructor to initialize the parameters.
     *
     * This constructor initializes the parameters for a cuboid in the simulation.
     *
     * @param llfCorner The coordinate of the lower left front-side corner of the cuboid.
     * @param numParticles The number of particles in each dimension of the cuboid.
     * @param pDistance The distance between particles (mesh width of the grid).
     * @param pMass The mass of one particle.
     * @param startV The initial velocity of the particles in each dimension.
     * @param meanV The mean-value of the velocity of the Brownian Motion.
     * @param temp The temperature for the Maxwell-Boltzmann distribution.
     */
    CuboidParameters(std::array<double, 3> llfCorner, std::array<std::size_t, 3> numParticles, double pDistance,
                     double pMass,
                     std::array<double, 3> startV, double meanV, double temp)
            : lowerLeftFrontCorner(llfCorner), numParticlesPerDimension(numParticles), particleDistance(pDistance),
              particleMass(pMass), initialVelocity(startV), meanVelocity(meanV), temperature(temp) {}
};