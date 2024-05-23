//
// Created by kimj2 on 07.05.2024.
//
#pragma once

#include "../../objects/ParticleContainer.h"
#include "CuboidParameters.h"
#include "ParticleParameters.h"

class ParticleGenerator {

public:
    ParticleGenerator() = default;

    ~ParticleGenerator() = default;

    static Particle generateParticle(const ParticleParameters &parameters);

    static void generateCuboid(const CuboidParameters &parameters, ParticleContainer& particleContainer);
};
