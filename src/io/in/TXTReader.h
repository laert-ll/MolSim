
/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include <gtest/gtest.h>

#include "../../objects/ParticleContainer.h"
#include "ParticleGenerator.h"
#include "FileReader.h"

namespace fileReaders {

    class TXTReader : public FileReader {

    public:

        TXTReader() = default;

        ~TXTReader() override = default;

        static ParticleContainer readFile(const std::string &filepath);

        static const std::set<int> allowedDataCodes;
        static const std::set<int> allowedDimensions;

        /**
        * Reads particle data from a file and returns a ParticleContainer.
        *
        * @param filepath The path to the file to read particle data from.
        * @return A ParticleContainer containing the particles read from the file.
        */
        static void loadParticles(const std::vector<std::string> &lines, ParticleContainer &particles);

        static void loadCuboids(const std::vector<std::string> &lines, ParticleContainer &particles);

        static void loadDiscs(const std::vector<std::string> &lines, ParticleContainer &particles);

        /**
        * This method parses an array of values from a single line (string)
        * and update the data object, specified as parameter, accordingly.
        *
        * @tparam T type of 'data'
        * @tparam N array size of 'data'
        * @param line current file line
        * @param data data object to update according to the given line
        */
        template<typename T, size_t N>
        static void parseDataFromLine(std::istringstream &datastream, std::array<T, N> &data);

        /**
        * This method reads the file specified by the parameter 'filepath'
        * and returns only relevant lines (that are no comments) in the file as a vector strings.
        *
        * Moreover, this functions checks if the given "number of cuboid" in the input file is non-negative or not.
        *
        * @param filepath
        * @return vector of strings
        */
        static std::vector<std::string> readFileLines(const std::string &filepath);

        /**
        * This method validates the header lines of the input file.
        * The header lines should contain the data code, number of data sets, and the dimension of the simulation.
        *
        * This method checks if the header data are allowed and returns error exitcode, if not.
        *
        * @param lines
        */
        static void validateHeaderLines(const std::vector<std::string> &lines);

    };
}// namespace fileReaders
