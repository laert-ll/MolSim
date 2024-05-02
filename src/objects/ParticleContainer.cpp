#include "ParticleContainer.h"
#include <algorithm>

const double VOLUME_MIN = 0.5;
const double VOLUME_MAX = 1.0;

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
