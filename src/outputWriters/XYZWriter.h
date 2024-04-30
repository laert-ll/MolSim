/*
 * XYZWriter.h
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#pragma once

#include "../Particle.h"
#include "OutputWriter.h"

#include <fstream>
#include <list>

namespace outputWriters {

    class XYZWriter : public OutputWriter {

    public:
        XYZWriter() = default;

        virtual ~XYZWriter() = default;

        void plotParticles(int iteration, ParticleContainer &particleContainer, const std::string &filename);

    };
}// namespace outputWriters
