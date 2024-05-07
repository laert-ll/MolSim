//
// Created by kimj2 on 07.05.2024.
//
#include "ParticleGenerator.h"

Particle ParticleGenerator::generateParticle(const ParticleParameters &parameters) {
    return Particle(parameters.getPosition(),
                    parameters.getVelocity(),
                    parameters.getMass(),
                    parameters.getVolume(),
                    parameters.getType());
}

ParticleContainer ParticleGenerator::readCuboidParameters(const CuboidParameters &parameters) {
    return ParticleContainer();
}
