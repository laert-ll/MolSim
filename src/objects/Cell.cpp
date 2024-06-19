#include "Cell.h"
#include "Particle.h"

void Cell::addParticle(std::shared_ptr<Particle> particle) {
    particles.insert(particle);
}

void Cell::removeParticle(std::shared_ptr<Particle> particle) {
    particles.erase(particle);
}

void Cell::addNeighbor(std::shared_ptr<Cell> cell) {
    neighboringCells.push_back(cell);
}

std::unordered_set<std::shared_ptr<Particle>>& Cell::getParticles() {
    return particles;
}

std::vector<std::shared_ptr<Cell>>& Cell::getNeighboringCells() {
    return neighboringCells;
}

int Cell::getNeighboringCellsSize() {
    return neighboringCells.size();
}

std::array<size_t, 3> Cell::getIndex(){
    return index;
}
