//
// Created by Ujin on 04.05.2024.
//

#include "ParticleGenerator.h"


ParticleContainer ParticleGenerator::generateParticles(std::array<double, 3> x, std::array<double, 3> n, double h, double m, std::array<double, 3> v, double k_B, double t) {    ParticleContainer result;
    for (int i = 0; i < n[0]; i++) {
        for (int j = 0; j < n[1]; j++) {
            for (int k = 0; k < n[2]; k++) {
                result.addParticle(Particle({x[0] + i * h, x[1] + j * h, x[2] + k * h}, v, m, 3));
            }
        }
    }
    calculateVelocities(result, v, m ,k_B, t);
    return result;
};

void ParticleGenerator::calculateVelocities(ParticleContainer& container, std::array<double, 3> v, double m, double k_B, double t) {
    // since it's always the same temperature, mass and velocities, calculate it once and set it for every particle.
    std::array<double, 3> resultV = v;
    for (int i = 0; i < 3; i++) {
        resultV[i] = pow(m/ (2 * k_B * t * M_PI), 0.5) * exp(-m * v[i] * v[i] / (2 * k_B * t));
    }
    for (auto it = container.begin(); it != container.end(); ++it) {
    Particle& particle = *it;
    particle.setX(resultV);
    }
};