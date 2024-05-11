/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include "../../objects/ParticleContainer.h"
#include "CuboidParameters.h"
#include "ParticleGenerator.h"

/**
 * @class FileReader
 * A class responsible for reading particle data from a file.
 */
class FileReader {

public:
    /**
     * Constructor that initializes the particleGenerator.
     *
     * @param generator The ParticleGenerator to use for particle data.
     */
    FileReader() = default;


    ~FileReader() = default;

    /**
     * Reads particle data from a file and returns a ParticleContainer.
     *
     * @param filepath The path to the file to read particle data from.
     * @return A ParticleContainer containing the particles read from the file.
     */
    static ParticleContainer loadParticles(const std::string& filepath);

    static ParticleContainer loadCuboid(const std::string& filepath);
};
