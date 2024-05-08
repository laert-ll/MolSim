//
// Created by kimj2 on 30.04.2024.
//

#pragma once

#include "../objects/ParticleContainer.h"

namespace outputWriters {

    /**
     * Abstract base class for output writers.
     */
    class OutputWriter {
    public:
        OutputWriter() = default;

        virtual ~OutputWriter() = default;

        /**
         * Method to plot the particles.
         * @param iteration the current iteration
         * @param particleContainer the container of particles
         * @param filename the filename to write the plot to
         */
        virtual void plotParticles(int iteration, ParticleContainer& particleContainer, const std::string& filename) = 0;
    };
}