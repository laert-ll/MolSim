//
// Created by kimj2 on 07.05.2024.
//
#pragma once

#include "../../objects/ParticleContainer.h"
#include "io/in/parameters/CuboidParameters.h"
#include "io/in/parameters/ParticleParameters.h"
#include "io/in/parameters/DiscParameters.h"
#include "objects/LinkedCellContainer.h"

class ParticleGenerator {

public:
    ParticleGenerator() = default;

    ~ParticleGenerator() = default;

    static Particle generateParticle(const ParticleParameters &parameters);

    static void generateCuboid(const CuboidParameters &parameters, ParticleContainer& particleContainer);

    static void generateCuboid(const CuboidParameters &parameters, LinkedCellContainer& linkedCellContainer, size_t &id_arg);

    static void generateDisc(const DiscParameters &parameters, ParticleContainer& particleContainer);

    static void generateDisc(const DiscParameters &parameters, LinkedCellContainer& linkedCellContainer, size_t &id_arg);
};
