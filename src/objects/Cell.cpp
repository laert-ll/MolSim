#include "Cell.h"
#include <algorithm>

Cell::Cell(const std::array<double, 2>& start_coordinates, const std::array<double, 2>& end_coordinates)
    : start_coordinates(start_coordinates), end_coordinates(end_coordinates) {}

std::array<double, 2>& Cell::getStartCoordinates() {
    return start_coordinates;
}
    
std::array<double, 2>& Cell::getEndCoordinates() {
    return end_coordinates;
}

void Cell::addParticle(Particle& particle) {
    particles.push_back(std::ref(particle));
}

void Cell::removeParticle(Particle& particle) {
    auto it = std::find_if(particles.begin(), particles.end(),
                           [&](const std::reference_wrapper<Particle>& ref) {
                               return &ref.get() == &particle;
                           });
    if (it != particles.end()) {
        particles.erase(it);
    }
}

std::vector <std::reference_wrapper<Particle>>::iterator Cell::begin() {
    return particles.begin();
}

std::vector <std::reference_wrapper<Particle>>::iterator Cell::end() {
    return particles.end();
}
