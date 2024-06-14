//
// Created by kimj2 on 07.05.2024.
//
#pragma once

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
    double distance;

    /**
     * @brief Mass of one particle.
     */
    double m;

    /**
     * @brief Initial velocity of the particles in each dimension.
     */
    std::array<double, 3> startV;

    /**
     * @brief Mean-value of the velocity of the Brownian Motion.
     */
    double meanV;


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
     */
    CuboidParameters(std::array<double, 3> llfCorner, std::array<std::size_t, 3> numParticles, double pDistance,
                     double pMass,
                     std::array<double, 3> startV, double meanV)
            : lowerLeftFrontCorner(llfCorner), numParticlesPerDimension(numParticles), distance(pDistance),
              m(pMass), startV(startV), meanV(meanV){}
};