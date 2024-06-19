#pragma once

#include "Particle.h"

#include <unordered_set>
#include <vector>

class Cell {
public:
    Cell() = default;

    Cell(size_t xIndex, size_t yIndex, size_t zIndex, double cellSizeX, double cellSizeY, double cellSizeZ)
            : index{xIndex, yIndex, zIndex}, dimensions{cellSizeX, cellSizeY, cellSizeZ} {}

    void addParticle(Particle* particle);
    void removeParticle(Particle* particle);
    void addNeighbor(Cell* cell);
    std::unordered_set<Particle*>& getParticles();
    std::vector<Cell*>& getNeighboringCells();
    int getNeighboringCellsSize();
    std::array<size_t, 3> getIndex();

private:
    std::array<size_t, 3> index;
    std::array<double, 3> dimensions;
    std::unordered_set<Particle*> particles;
    std::vector<Cell*> neighboringCells;
};
