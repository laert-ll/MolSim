//
// Created by Ujin on 04.05.2024.
//


#ifndef PSEMOLDYN_GROUPC_PARTICLEGENERATOR_H
#define PSEMOLDYN_GROUPC_PARTICLEGENERATOR_H
#include "ParticleContainer.h"
#include <cmath>

class ParticleGenerator {

public:
    /**
 * @brief Generates particles in a container based on given parameters.
 *
 * @param x The coordinate of the lower left front-side corner.
 * @param n Number of particles per dimension: N1 × N2 × N3.
 * @param h Distance between particles (mesh width of the grid).
 * @param m Mass of one particle.
 * @param v Initial velocity of the particles (3 Components).
 * @param t Temperature, used to calculate mean-value of Brownian Motion.
 *
 * @return ParticleContainer containing generated particles.
 */
    ParticleContainer generateParticles(std::array<double, 3> x, std::array<double, 3> n, double h, double m, std::array<double, 3> v,
                      double k_B, double t);

/**
 * \brief Calculates velocities for particles in a container.
 *
 * This function calculates the velocities of particles in the provided container
 * based on their masses, temperature, and the Boltzmann constant.
 *
 * \param container Pointer to the container holding the particles.
 * \param m Mass of the particles.
 * \param k_B Boltzmann constant.
 * \param t Temperature.
 * \return An std::array<double, 3> containing the velocities.
 */
    static void calculateVelocities(ParticleContainer& container, std::array<double, 3> v, double m, double k_B, double t);
    };
#endif //PSEMOLDYN_GROUPC_PARTICLEGENERATOR_H


