/*
 * XYZWriter.h
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#pragma once

#include "../../objects/Particle.h"
#include "FileWriter.h"

#include <fstream>
#include <list>

namespace outputWriters {
    /**
     * @class XYZWriter
     * @brief Concrete output writer class that writes particles' positions to an XYZ file.
     *
     * This class is a concrete implementation of the `OutputWriter` base class.
     * It provides an implementation for the `plotParticles` method, which writes the positions of particles in the provided particle container to an XYZ file.
     */
    class XYZWriter : public OutputWriter {

    public:
        XYZWriter() = default;

        virtual ~XYZWriter() = default;

        /**
         * @brief Writes the particles' positions to an XYZ file.
         *
         * This method writes the positions of all particles in the provided particle container to an XYZ file.
         *
         * @param iteration The current iteration number, which is used to generate a unique filename for the output file.
         * @param particleContainer The container of particles whose positions will be written to the file.
         * @param filename The base name of the file to be written. The iteration number will be appended to this name to create a unique filename for each output file.
         *
         * @note The XYZ file will be written to the current working directory.
         */
        void plotParticles(int iteration, ParticleContainer &particleContainer, const std::string &filename);
    };
}// namespace out
