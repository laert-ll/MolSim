/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include "../../objects/ParticleContainer.h"
#include "CuboidParameters.h"

/**
 * @class FileReader
 * A class responsible for reading particle data from a file.
 */
class FileReader {

public:
    FileReader();

    virtual ~FileReader();

    /**
     * Reads particle data from a file and returns a ParticleContainer.
     *
     * @param filepath The path to the file to read particle data from.
     * @return A ParticleContainer containing the particles read from the file.
     */
    ParticleContainer readParticleData(const std::string& filepath, const ParticleGenerator &generator);

    CuboidParameters readCuboidParameters(const std::string& filepath, const ParticleGenerator &generator);
};
