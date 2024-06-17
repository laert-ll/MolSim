#include "Cell.h"
#include "Particle.h"

Cell::Cell() {}

Cell::Cell(int xIndex, int yIndex, int zIndex, double cellSizeX, double cellSizeY, double cellSizeZ) {
    index[0] = xIndex;
    index[1] = yIndex;
    index[2] = zIndex;

    dimensions[0] = cellSizeX;
    dimensions[1] = cellSizeY;
    dimensions[2] = cellSizeZ;
}

void Cell::addParticle(Particle* particle) {
    particles.insert(particle);
}

void Cell::removeParticle(Particle* particle) {
    particles.erase(particle);
}

void Cell::addNeighbor(Cell* cell) {
    neighboringCells.push_back(cell);
}

std::unordered_set<Particle*>& Cell::getParticles() {
    return particles;
}

std::vector<Cell*>& Cell::getNeighboringCells() {
    return neighboringCells;
}

int Cell::getNeighboringCellsSize() {
    return neighboringCells.size();
}

std::array<int, 3> Cell::getIndex() {
    return index;
}
