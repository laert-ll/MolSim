//
// Created by kimj2 on 30.04.2024.
//

#pragma once

#include "../ParticleContainer.h"

namespace outputWriters {

    class OutputWriter {
    public:
        OutputWriter() = default;

        virtual ~OutputWriter() = default;

        virtual void plotParticles(int iteration, ParticleContainer &particleContainer, const std::string &filename) {}

    };
}