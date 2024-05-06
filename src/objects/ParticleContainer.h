#pragma once

#include "Particle.h"

#include <vector>
#include <functional>
#include <cmath>

/**
 * Container to store particles and provide iterators for them.
 */
class ParticleContainer {
private:
    /**
     * A vector to store the particles.
     */
    std::vector<Particle> particles;
    /**
     * A vector to store all unique pairs of particles (as references).
     */
    std::vector<std::pair<std::reference_wrapper<Particle>, std::reference_wrapper<Particle>>> particlePairs;

public:
    ParticleContainer();

    ~ParticleContainer();

    /**
     * Method to add a particle to the container.
     * @param particle the particle to add
     */
    void addParticle(const Particle& particle);

    /**
     * Method to fill the vector of unique pairs with the references to particles.
     */
    void initializePairs();

    /**
     * Method to set volumes to particles proportional to their masses for paraview visualization purposes.
     */
    void setVolumes();

    /**
     * Begin iterator for the particles.
     * @return an iterator to the beginning of the particles
     */
    std::vector<Particle>::iterator begin();

    /**
     * End iterator for the particles.
     * @return an iterator to the end of the particles
     */
    std::vector<Particle>::iterator end();

    /**
     * Begin iterator for the particle pairs.
     * @return an iterator to the beginning of the particle pairs
     */
    std::vector<std::pair<std::reference_wrapper<Particle>, std::reference_wrapper<Particle>>>::iterator pair_begin();

    /**
     * End iterator for the particle pairs.
     * @return an iterator to the end of the particle pairs
     */
    std::vector<std::pair<std::reference_wrapper<Particle>, std::reference_wrapper<Particle>>>::iterator pair_end();

    /**
     * Get the number of particles in the container.
     * @return the number of particles
     */
    size_t getSize() const;

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
   static ParticleContainer generateCuboid(std::array<double, 3> x, std::array<double, 3> n, double h, double m, std::array<double, 3> v,
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
 void calculateVelocities(std::array<double, 3> v, double m, double k_B, double t);
};