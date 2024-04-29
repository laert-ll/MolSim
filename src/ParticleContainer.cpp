#include "ParticleContainer.h"

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
