#pragma once

#include "Particle.h"

#include <unordered_set>
#include <vector>

class Cell {
public:
    Cell();
    Cell(int xIndex, int yIndex, int zIndex, double cellSizeX, double cellSizeY, double cellSizeZ);

    void addParticle(Particle* particle);
    void removeParticle(Particle* particle);
    void addNeighbor(Cell* cell);
    std::unordered_set<Particle*>& getParticles();
    std::vector<Cell*>& getNeighboringCells();
    int getNeighboringCellsSize();
    std::array<int, 3> getIndex();

private:
    std::array<int, 3> index;
    double dimensions[3];
    std::unordered_set<Particle*> particles;
    std::vector<Cell*> neighboringCells;
};
