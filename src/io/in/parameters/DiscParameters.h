//
// Created by kimj2 on 24.05.2024.
//
#pragma once

#include <array>

/**
 * @class DiscParameters
 * @brief Class to hold the parameters needed to generate a disc of particles.
 */
class DiscParameters {
public:
    /**
     * @brief Construct a new Disc Parameters object
     *
     * @param center Center coordinates of the disc
     * @param startV Initial velocities of all particles in the disc
     * @param numParticlesAlongRadius Number of particles along the radius of the disc
     * @param distance Distance between the particles
     * @param mass Mass of the particles
     * @param dimension Dimension of the simulation
     */
    DiscParameters(const std::array<double, 3> &center, const std::array<double, 3> &startV,
                   int numParticlesAlongRadius, double distance, double mass, int dimension)
            : center(center), startV(startV), numParticlesAlongRadius(numParticlesAlongRadius), distance(distance),
              mass(mass), dimension(dimension) {}

    /**
     * @brief Get the Center coordinates of the disc
     *
     * @return const std::array<double, 3>&
     */
    [[nodiscard]] const std::array<double, 3> &getCenter() const { return center; }

    /**
     * @brief Get the Initial velocity of the disc
     *
     * @return const std::array<double, 3>&
     */
    [[nodiscard]] const std::array<double, 3> &getStartV() const { return startV; }

    /**
     * @brief Get the Number of particles along the radius of the disc
     *
     * @return int
     */
    [[nodiscard]] int getNumParticlesAlongRadius() const { return numParticlesAlongRadius; }

    /**
     * @brief Get the Distance between the particles
     *
     * @return double
     */
    [[nodiscard]] double getDistance() const { return distance; }

    /**
     * @brief Get the Mass of the particles
     *
     * @return double
     */
    [[nodiscard]] double getMass() const { return mass; }

    /**
     * @brief Get the Dimension of the simulation
     *
     * @return int
     */
    [[nodiscard]] int getDimension() const { return dimension; }

private:
    const std::array<double, 3> center;
    const std::array<double, 3> startV;
    const int numParticlesAlongRadius;
    const double distance;
    const double mass;
    const int dimension;
};