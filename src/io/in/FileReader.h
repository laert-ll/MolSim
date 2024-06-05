//
// Created by kimj2 on 04.06.2024.
//

#pragma once

#include "../../objects/ParticleContainer.h"
#include "parameters/SimulationDataContainer.h"

namespace fileReaders {
    /**
     * @class FileReader
     * @brief Abstract base class for file readers.
     *
     * This class is an abstract base class for file readers.
     * It provides a pure virtual method `readFile` that must be implemented by concrete subclasses.
     */
    class FileReader {
    public:
        FileReader() = default;

        virtual ~FileReader() = default;

        /**
         * @brief Reads a file and populates the provided particle container.
         *
         * This method reads a file and populates the provided particle container with the particles
         * described in the file.
         *
         * @param filename The name of the file to read.
         * @param particleContainer The container of particles to populate with the particles from the file.
         */
        virtual SimulationDataContainer readFile(const std::string &filepath) = 0;
    };
}// namespace fileReaders