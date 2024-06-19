#include "Cell.h"
#include "Particle.h"

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

std::array<size_t, 3> Cell::getIndex(){
    return index;
}
