#include "ParticleContainer.h"
#include <algorithm>
#include <stdexcept>

const double VOLUME_MIN = 0.5;
const double VOLUME_MAX = 1.0;

void ParticleContainer::addParticle(const Particle &particle) {
    particles.push_back(particle);
}

void ParticleContainer::deleteParticle(const Particle &particle) {
    // Find the particle in the vector
    auto it = std::find_if(particles.begin(), particles.end(), [&](const Particle &p) {
        return p == particle;
    });

    // If the particle is found, erase it from the vector
    if (it != particles.end()) {
        particles.erase(it);
    }
    particlePairs.clear();
    initializePairs();
}

bool ParticleContainer::pairExists(const Particle &particle1, const Particle &particle2) const {
    for (const auto &pair : particlePairs) {
        if ((&pair.first.get() == &particle1 && &pair.second.get() == &particle2) ||
            (&pair.first.get() == &particle2 && &pair.second.get() == &particle1)) {
            return true;
        }
    }
    return false;
void ParticleContainer::addCell(const std::array<double, 2>& start_coordinates, 
                                const std::array<double, 2>& end_coordinates) {
    Cell newCell = Cell(start_coordinates, end_coordinates);
    cells.push_back(newCell);
}

void ParticleContainer::initializeNeighboringCells() {
    double cutoff = 3.0;
    for (auto& cell : cells) {
        auto& start = cell.getStartCoordinates();
        auto& end = cell.getEndCoordinates();

        for (auto& otherCell : cells) {
            if (&cell == &otherCell) continue;

            auto& otherStart = otherCell.getStartCoordinates();
            auto& otherEnd = otherCell.getEndCoordinates();

            if ((start[0] < otherStart[0] || start[0] == otherStart[0]) &&
                (start[1] < otherStart[1] || start[1] == otherStart[1]) &&
                (end[0] > otherEnd[0] || end[0] == otherEnd[0]) &&
                (end[1] > otherEnd[1] || end[1] == otherEnd[1])) {
                if (std::abs(start[0] - otherStart[0]) <= cutoff &&
                    std::abs(start[1] - otherStart[1]) <= cutoff) {
                    cell.neighboring_cells.push_back(otherCell);
                }
            }
        }
    }
}

void ParticleContainer::initializePairs() {
    for (auto it1 = particles.begin(); it1 != particles.end(); ++it1)
        for (auto it2 = std::next(it1); it2 != particles.end(); ++it2)
            if (!pairExists(*it1, *it2))
                particlePairs.push_back({*it1, *it2});
}

void ParticleContainer::arrangeCells() {
    particlePairs.clear();

    for (auto &cell : cells) {
        auto& start = cell.getStartCoordinates();
        auto& end = cell.getEndCoordinates();

        for (auto particle = cell.begin(); particle != cell.end(); ++particle) {
            auto& pos = particle->get().getX();
            if (pos[0] < start[0] || pos[0] >= end[0] || 
                pos[1] < start[1] || pos[1] >= end[1]) {
                cell.removeParticle(particle->get());
                reassign(particle->get());
            }
        }
    }
}

void ParticleContainer::reassign(Particle &particle) {
    auto& pos = particle.getX();
    for (auto &cell : cells) {
        auto& start = cell.getStartCoordinates();
        auto& end = cell.getEndCoordinates();
        if (pos[0] >= start[0] && pos[0] < end[0] && 
            pos[1] >= start[1] && pos[1] < end[1]) {
            cell.addParticle(particle);
        }
    }
}

std::vector<std::reference_wrapper<Particle>> ParticleContainer::getNeighboringParticles(const Particle& particle) {
    std::vector<std::reference_wrapper<Particle>> neighboring_particles;

    Cell cell = findCell(particle);

    neighboring_particles.insert(neighboring_particles.end(), cell.begin(), cell.end());

    for (auto& neighbor : cell.neighboring_cells) {
        neighboring_particles.insert(neighboring_particles.end(), neighbor.get().begin(), neighbor.get().end());
    }

    return neighboring_particles;
}

Cell ParticleContainer::findCell(const Particle& particle) {
    auto position = particle.getX();
    for (auto& cell : cells) {
        auto& start = cell.getStartCoordinates();
        auto& end = cell.getEndCoordinates();
        if (position[0] >= start[0] && position[0] < end[0] &&
            position[1] >= start[1] && position[1] < end[1]) {
            return cell;
        }
    }
    throw std::out_of_range("No cell found for the particle");
}

void ParticleContainer::setVolumes() {
    // Find the particle with the highest and lowest masses
    auto mass_minmax = std::minmax_element(particles.begin(), particles.end(),
                                           [](const Particle& a, const Particle& b) {
                                               return a.getM() < b.getM();
                                           });

    double min_mass = (*mass_minmax.first).getM();
    double max_mass = (*mass_minmax.second).getM();

    // Calculate scaling factors
    double mass_range = max_mass - min_mass;
    double volume_range = VOLUME_MAX - VOLUME_MIN;
    double scaling_factor = volume_range / mass_range;

    // Scale volume for each object
    for (auto& p : particles) {
        double volume = VOLUME_MIN + scaling_factor * p.getM();
        p.setVolume(volume);
    }
}

std::vector<Particle>::iterator ParticleContainer::begin() {
    return particles.begin();
}

std::vector<Particle>::iterator ParticleContainer::end() {
    return particles.end();
}

std::vector <std::pair<std::reference_wrapper < Particle>, std::reference_wrapper<Particle>>>
::iterator ParticleContainer::pair_begin() {
    return particlePairs.begin();
}

std::vector <std::pair<std::reference_wrapper < Particle>, std::reference_wrapper<Particle>>>
::iterator ParticleContainer::pair_end() {
    return particlePairs.end();
}

size_t ParticleContainer::getSize() const {
    return particles.size();
}

std::vector<Particle> ParticleContainer::getParticles() const {
    return particles;
};
