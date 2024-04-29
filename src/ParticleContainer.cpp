#include "ParticleContainer.h"
#include <algorithm>
#include <cmath>

ParticleContainer::ParticleContainer() {}

ParticleContainer::~ParticleContainer() {}

void ParticleContainer::addParticle(const Particle &particle) {
    particles.push_back(particle);
}

void ParticleContainer::initializePairs() {
    for (auto it1 = particles.begin(); it1 != particles.end(); ++it1)
        for (auto it2 = std::next(it1); it2 != particles.end(); ++it2)
            particlePairs.push_back({*it1, *it2});
}

void ParticleContainer::setVolumes() {
    // Find the particle with the highest and lowest masses
    auto mass_range = std::minmax_element(particles.begin(), particles.end(),
        [](const Particle& a, const Particle& b) {
            return a.getM() < b.getM();
        });

    double min_mass = (*mass_range.first).getM();
    double max_mass = (*mass_range.second).getM();

    // Calculate scaling factors
    double mass_range_diff = max_mass - min_mass;
    double volume_range_diff = 1.0 - 0.5; // New volume range
    double scaling_factor = volume_range_diff / mass_range_diff;

    // Set volumes for all particles
    for (auto& p : particles) {
        double volume = 0.5 + scaling_factor * (p.getM() - min_mass); // Adjusted volume calculation
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
