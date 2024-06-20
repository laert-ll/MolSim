//
// Created by kimj2 on 07.05.2024.
//
#pragma once

#include <array>

/**
 * @class CuboidParameters
 * @brief Parameters for a cuboid.
 *
 * This class encapsulates the parameters needed to define a cuboid.
 * All attributes are private, const and can only be accessed through getter methods.
 */
class CuboidParameters {
public:
    /**
     * @brief Constructor with initializer list.
     * @param llfCorner Lower left front corner of the cuboid.
     * @param numParticles Number of particles per dimension in the cuboid.
     * @param pDistance Distance between particles.
     * @param pMass Mass of the particles.
     * @param startV Initial velocity of the particles.
     * @param meanV Mean velocity of the particles.
     * @param dimension Dimension of the cuboid.
     */
    CuboidParameters(std::array<double, 3> llfCorner, std::array<std::size_t, 3> numParticles, double pDistance,
                     double pMass, std::array<double, 3> startV, double meanV, int dimension, double sigma, double epsilon)
            : lowerLeftFrontCorner(llfCorner), numParticlesPerDimension(numParticles), distance(pDistance),
              m(pMass), startV(startV), meanV(meanV), dimension(dimension), sigma(sigma), epsilon(epsilon){}

    /**
     * @brief Get the lower left front corner of the cuboid.
     * @return The lower left front corner of the cuboid.
     */
    [[nodiscard]] const std::array<double, 3>& getLowerLeftFrontCorner() const {
        return lowerLeftFrontCorner;
    }

    /**
     * @brief Get the number of particles per dimension in the cuboid.
     * @return The number of particles per dimension in the cuboid.
     */
    [[nodiscard]] const std::array<std::size_t, 3>& getNumParticlesPerDimension() const {
        return numParticlesPerDimension;
    }

    /**
     * @brief Get the distance between particles in the cuboid.
     * @return The distance between particles in the cuboid.
     */
    [[nodiscard]] double getDistance() const {
        return distance;
    }

    /**
     * @brief Get the mass of the particles in the cuboid.
     * @return The mass of the particles in the cuboid.
     */
    [[nodiscard]] double getMass() const {
        return m;
    }

    /**
     * @brief Get the initial velocity of the particles in the cuboid.
     * @return The initial velocity of the particles in the cuboid.
     */
    [[nodiscard]] const std::array<double, 3>& getStartV() const {
        return startV;
    }

    /**
     * @brief Get the mean velocity of the particles in the cuboid.
     * @return The mean velocity of the particles in the cuboid.
     */
    [[nodiscard]] double getMeanV() const {
        return meanV;
    }

    /**
     * @brief Get the dimension of the cuboid.
     * @return The dimension of the cuboid.
     */
    [[nodiscard]] int getDimension() const {
        return dimension;
    }

    double getSigma() const {
        return sigma;
    }

    double getEpsilon() const {
        return epsilon;
    }

private:
    /**
     * @brief Lower left front corner of the cuboid.
     */
    const std::array<double, 3> lowerLeftFrontCorner;

    /**
     * @brief Number of particles per dimension in the cuboid.
     */
    const std::array<std::size_t, 3> numParticlesPerDimension;

    /**
     * @brief Distance between particles in the cuboid.
     */
    const double distance;

    /**
     * @brief Mass of the particles in the cuboid.
     */
    const double m;

    /**
     * @brief Initial velocity of the particles in the cuboid.
     */
    const std::array<double, 3> startV;

    /**
     * @brief Mean velocity of the particles in the cuboid.
     */
    const double meanV;

    /**
     * @brief Dimension of the cuboid.
     */
    const int dimension;

    const double sigma;
    const double epsilon;
};