//
// Created by kimj2 on 07.05.2024.
//
#pragma once

#include "../../objects/ParticleContainer.h"
#include "./parameters/CuboidParameters.h"
#include "./parameters/ParticleParameters.h"
#include "./parameters/DiscParameters.h"

class ParticleGenerator {

public:
    ParticleGenerator() = default;

    ~ParticleGenerator() = default;

    static Particle generateParticle(const ParticleParameters &parameters);

    static void generateCuboid(const CuboidParameters &parameters, ParticleContainer& particleContainer);

    static void generateDisc(const DiscParameters &parameters, ParticleContainer& particleContainer);

};
