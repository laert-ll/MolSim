#pragma once

#include "Particle.h"
#include <array>
#include <vector>
#include <functional>

class Particle;

class Cell {
public:
    Cell(const std::array<double, 2>& start_coordinates, const std::array<double, 2>& end_coordinates);

    std::array<double, 2>& getStartCoordinates();
    std::array<double, 2>& getEndCoordinates();

    std::vector<std::reference_wrapper<Particle>> particles;
    std::vector<std::reference_wrapper<Cell>> neighboring_cells;

    void addParticle(Particle& particle);
    void removeParticle(Particle& particle);

    std::vector<std::reference_wrapper<Particle>>::iterator begin();
    std::vector<std::reference_wrapper<Particle>>::iterator end();

private:
    std::array<double, 2> start_coordinates;
    std::array<double, 2> end_coordinates;
};
