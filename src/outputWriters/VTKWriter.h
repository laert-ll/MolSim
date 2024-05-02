/*
 * VTKWriter.h
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#pragma once

#include "../objects/Particle.h"
#include "vtk-unstructured.h"
#include "OutputWriter.h"

#include <list>

namespace outputWriters {

    /**
     * This class implements the functionality to generate vtk output from
     * particles.
     */
    class VTKWriter : public OutputWriter {

    public:
        VTKWriter() = default;

        virtual ~VTKWriter() = default;

        /**
         * @brief Plots particles to a VTK file.
         *
         * This method initializes the output for the VTK file by setting up the necessary data structures and prepares to plot particles.
         * It then iterates over all particles in the provided particle container and plots each particle using the `plotParticle` method.
         * Finally, it writes the completed VTK file to disk.
         *
         * @param iteration The current iteration number, which is used to generate a unique filename for the output file.
         * @param particleContainer The container of particles to be plotted.
         * @param filename The base name of the file to be written. The iteration number will be appended to this name to create a unique filename for each output file.
         *
         * @note The VTK file will be written to the current working directory.
         */
        void plotParticles(int iteration, ParticleContainer &particleContainer, const std::string &filename);

    private:


        VTKFile_t *vtkFile;

        /**
         * set up internal data structures and prepare to plot a particle.
         */
        void initializeOutput(int numParticles);

        /**
         * plot type, mass, position, velocity and force of a particle.
         *
         * @note: initializeOutput() must have been called before.
         */
        void plotParticle(Particle &p);

        /**
         * writes the final output file.
         *
         * @param filename the base name of the file to be written.
         * @param iteration the number of the current iteration,
         *        which is used to generate an unique filename
         */
        void writeFile(const std::string &filename, int iteration);
    };

} // namespace outputWriters
