
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

        static ParticleContainer readFile(const std::string& filepath);

        /**
        * Reads particle data from a file and returns a ParticleContainer.
        *
        * @param filepath The path to the file to read particle data from.
        * @return A ParticleContainer containing the particles read from the file.
        */
        static void loadParticles(const std::vector<std::string>& lines, ParticleContainer& particles);

        static void loadCuboids(const std::vector<std::string>& lines, ParticleContainer& particles);



        /**
        * This method parses an array of values from a single line (string)
        * and updateCells the data object, specified as parameter, accordingly.
        *
        * @tparam T type of 'data'
        * @tparam N array size of 'data'
        * @param line current file line
        * @param data data object to updateCells according to the given line
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
    * Class section end
    *
    *
    *
    * --------------------------------------------TEST SECTION------------------------------------------------------------
    * To be able to use the private methods and attributes in testing, FRIEND_TESTs are declared here.
    */
        FRIEND_TEST(FileReaderTest, LoadParticles);
        FRIEND_TEST(FileReaderTest, LoadCuboids);
        FRIEND_TEST(FileReaderTest, readFileLinesBasicTest);

    };
}// namespace fileReaders
