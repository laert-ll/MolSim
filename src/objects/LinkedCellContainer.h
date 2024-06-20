#pragma once

#include "Particle.h"
#include "Cell.h"
#include "../io/in/parameters/CuboidParameters.h"

#include <vector>

class LinkedCellContainer {

private:

    /**
    * A vector to store the particles.
    */
    std::vector<std::shared_ptr<Particle>> particles;

    /**
    * A 3D vector to store the cells.
    */
    std::vector<std::vector<std::vector<std::shared_ptr<Cell>>>> cells;

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

    //LinkedCellContainer(std::array<double, 3> &domain, std::vector<CuboidParameters> &cuboidParameters, double &cutoffRadius, double &cellSize);

    ~LinkedCellContainer() = default;

    void initializeAndPopulateCells();

    void setCutOffRadius(const double &cutoffRadius);

    void setCellSize(const double &cellSize);

    void setDomain(const std::array<double, 3> &domain);

    /**
    * Method to add a particle to the container.
    * @param particle the particle to add
    */
    void addParticle(const std::shared_ptr<Particle> &particle);

    /**
     * Begin iterator for the particles.
     * @return an iterator to the beginning of the particles
     */
    std::vector<std::shared_ptr<Particle>>::iterator begin();

    /**
     * End iterator for the particles.
     * @return an iterator to the end of the particles
     */
    std::vector<std::shared_ptr<Particle>>::iterator end();

    /**
    * Get the particles in the container.
    * @return a vector of all the particles
    */
    std::vector<std::shared_ptr<Particle>> getParticles() const;

    /**
    * Get the particles in the container.
    * @return a vector of all the particles
    */
    std::vector<std::vector<std::vector<std::shared_ptr<Cell>>>> getCells();

    /**
    * Get the number of particles in the container.
    * @return the number of particles
    */
    size_t getSize() const;

    void initializeCells();

    void initializeNeighbors();

    void populateCells();

    std::vector<std::shared_ptr<Cell>>& getNeighboringCellsIncludingSelf(const Particle &particle);

    /**
    * Method to add a cell to cells.
    */
    void addCell();

    /**
    * Method to update the cells and their particles.
    */
    void updateCells();


    std::array<size_t, 3> getIndex(const std::shared_ptr<Particle> &particle);

    bool hasZeroVelocities();

    std::array<size_t, 3> getIndex(const std::array<double, 3> positions);
};