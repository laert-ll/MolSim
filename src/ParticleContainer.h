#pragma once

#include "Particle.h"

#include <vector>
#include <functional>

/**
 * Container to store particles and provide interators for them.
 */
class ParticleContainer {
private:
    /**
     * A vector to store the particles.
     */
    std::vector <Particle> particles;
    /**
     * A vector to store all unique pairs of particles (as references).
     */
    std::vector <std::pair<std::reference_wrapper < Particle>, std::reference_wrapper<Particle>>>
    particlePairs;

public:
    ParticleContainer();

    ~ParticleContainer();

    /**
     * Method to add particles to the container.
     */
    void addParticle(const Particle &particle);

    /**
     * Method to fill the vector of unique pairs with the references to particles.
     */
    void initializePairs();

    /**
     * Method to set volumes to particles for paraview visualization purposes.
     */
    void setVolumes();

    /**
     * Begin iterator for the particles.
     */
    std::vector<Particle>::iterator begin();

    /**
     * End iterator for the particles.
     */
    std::vector<Particle>::iterator end();

    /**
     * Begin iterator for the particle pairs.
     */
    std::vector <std::pair<std::reference_wrapper < Particle>, std::reference_wrapper<Particle>>>

    ::iterator pair_begin();

    /**
     * End iterator for the particle pairs.
     */
    std::vector <std::pair<std::reference_wrapper < Particle>, std::reference_wrapper<Particle>>>

    ::iterator pair_end();

    /**
     * Get the number of particles in the container.
     */
    size_t getSize() const;
};
