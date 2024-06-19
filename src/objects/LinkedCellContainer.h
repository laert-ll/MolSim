#pragma once

#include "Particle.h"
#include "Cell.h"
#include "../io/in/CuboidParameters.h"

#include <vector>

class LinkedCellContainer {

private:

    /**
    * A vector to store the particles.
    */
    std::vector<Particle> particles;

    /**
    * A 3D vector to store the cells.
    */
    std::vector<std::vector<std::vector<Cell>>> cells;

    /**
    * The dimensions of the simulation
    */
    std::array<double, 3> domain;

    /**
    * Containers cutoff radius.
    */
    double cutoffRadius;

    /**
    * Normal size of the cells.
    */
    double cellSize;

public:

    LinkedCellContainer() = default;

    LinkedCellContainer(std::array<double, 3> &domain, std::vector<CuboidParameters> &cuboidParameters, double &cutoffRadius, double &cellSize);

    ~LinkedCellContainer() = default;

    /**
    * Method to add a particle to the container.
    * @param particle the particle to add
    */
    void addParticle(const Particle &particle);

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
    * Get the particles in the container.
    * @return a vector of all the particles
    */
    std::vector<Particle> getParticles() const;

    /**
    * Get the particles in the container.
    * @return a vector of all the particles
    */
    std::vector<std::vector<std::vector<Cell>>> getCells();

    /**
    * Get the number of particles in the container.
    * @return the number of particles
    */
    size_t getSize() const;

    void initializeCells();

    void initializeNeighbors();

    void generateCuboids(std::vector<CuboidParameters> &cuboidParameters);

    void populateCells();

    std::vector<Cell*>& getNeighboringCellsIncludingSelf(const Particle &particle);

    /**
    * Method to add a cell to cells.
    */
    void addCell();

    /**
    * Method to update the cells and their particles.
    */
    void update();


    std::array<size_t, 3> getIndex(Particle *particle);

};