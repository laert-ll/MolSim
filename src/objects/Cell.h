#pragma once

#include "Particle.h"

#include <unordered_set>
#include <vector>
#include <memory>

class Cell {
public:
    Cell() = default;

    Cell(size_t xIndex, size_t yIndex, size_t zIndex, double cellSizeX, double cellSizeY, double cellSizeZ)
            : index{xIndex, yIndex, zIndex}, dimensions{cellSizeX, cellSizeY, cellSizeZ} {}

    void addParticle(const std::shared_ptr<Particle>& particle);
    void removeParticle(const std::shared_ptr<Particle>& particle);
    void addNeighbor(const std::shared_ptr<Cell>& cell);
    std::unordered_set<std::shared_ptr<Particle>>& getParticles();
    std::vector<std::shared_ptr<Cell>>& getNeighboringCells();
    int getNeighboringCellsSize();
    std::array<size_t, 3> getIndex();

private:
    std::array<size_t, 3> index;
    std::array<double, 3> dimensions;
    std::unordered_set<std::shared_ptr<Particle>> particles;
    std::vector<std::shared_ptr<Cell>> neighboringCells;
};
