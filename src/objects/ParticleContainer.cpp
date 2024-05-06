#include "ParticleContainer.h"
#include <algorithm>
#include "utils/MaxwellBoltzmannDistribution.h"

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

//TODO: Rename variables in for-loop x-> corner, n
ParticleContainer ParticleContainer::generateCuboid(std::array<double, 3> x, std::array<double, 3> n, double h, double m, std::array<double, 3> v, double k_B, double t) {
    ParticleContainer result;
    for (int i = 0; i < n[0]; i++) {
        for (int j = 0; j < n[1]; j++) {
            for (int k = 0; k < n[2]; k++) {
                result.addParticle(Particle({x[0] + i * h, x[1] + j * h, x[2] + k * h}, v, m, 3));
            }
        }
    }
    result.calculateVelocities(v, m ,k_B, t);
    return result;
}

void ParticleContainer::calculateVelocities(std::array<double, 3> v, double m, double k_B, double t) {
    // since it's always the same temperature, mass and velocities, calculate it once and set it for every particle.
    double avgV = pow((v[0] * v[0] + v[1] * v[1] + v[2] * v[2]), 0.5);
    for (auto it = begin(); it != end(); ++it) {
        Particle& particle = *it;
        std::array<double, 3> randomV = maxwellBoltzmannDistributedVelocity(avgV,3);
        particle.setV(randomV);
    }
};
