//
// Created by kimj2 on 30.04.2024.
//

#pragma once

#include "objects/ParticleContainer.h"
#include "objects/LinkedCellContainer.h"

namespace outputWriters {

    /**
     * Abstract base class for output writers.
     */
    class FileWriter {
    public:
        FileWriter() = default;

        virtual ~FileWriter() = default;

        /**
         * Method to plot the particles.
         * @param iteration the current iteration
         * @param particleContainer the container of particles
         * @param filename the filename to write the plot to
         */
        virtual void plotParticles(int iteration, ParticleContainer& particleContainer, const std::string& filename) = 0;

        /**
         * Method to plot the particles.
         * @param iteration the current iteration
         * @param particleContainer the container of particles
         * @param filename the filename to write the plot to
         */
        virtual void plotParticlesLC(int iteration, LinkedCellContainer& linkedCellContainer, const std::string& filename) = 0;
    };
}