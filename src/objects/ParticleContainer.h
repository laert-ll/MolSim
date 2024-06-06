#pragma once

#include "Particle.h"
#include "Cell.h"

#include <vector>
#include <functional>
#include <cmath>

/**
 * Container to store particles and provide iterators for them.
 */
class ParticleContainer {
private:
    /**
     * Boundary
     */
    /**
     * A vector to store the particles.
     */
    std::vector<Particle> particles;
    /**
     * A vector to store all unique pairs of particles (as references).
     */
    std::vector<std::pair<std::reference_wrapper<Particle>, std::reference_wrapper<Particle>>> particlePairs;

    std::vector<Cell> cells;

public:

    ParticleContainer() = default;

    ~ParticleContainer() = default;

    /**
     * Method to add a particle to the container.
     * @param particle the particle to add
     */
    void addParticle(const Particle &particle);

    void addCell(std::array<double, 2>& start_coordinates, std::array<double, 2>& end_coordinates);

    void initializeNeighboringCells();

    /**
     * Method to remove a particle from the container.
     * @param particle the particle to remove
     */
    void deleteParticle(const Particle &particle);

    /**
     * Method to check if pair in ParticlePairs already exists
     */
    bool pairExists(const Particle &particle1, const Particle &particle2) const;

    /**
     * Method to fill the vector of unique pairs with the references to particles.
     */
    void initializePairs();

    void arrangeCells();

    std::vector<std::reference_wrapper<Particle>> getNeighboringParticles(const Particle& particle);

    Cell findCell(const Particle& particle);

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

    std::vector<Particle> getParticles() const;

    void reassign(Particle &particle);

};