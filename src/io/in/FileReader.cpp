/*
 * FileReader.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "FileReader.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

template<typename T, size_t N>
void parseDataFromLine(std::istringstream &datastream, std::array<T, N> &data);

std::vector<std::string> readFileLines(const std::string &filepath);

ParticleContainer FileReader::loadParticles(const std::string &filepath) {
    ParticleContainer particleContainer;
    std::array<double, 3> x{}, v{};
    double m;

    auto lines = readFileLines(filepath);
    int num_particles = std::stoi(lines[0]);

    for (int i = 1; i < num_particles + 1; ++i) {
        std::istringstream datastream(lines[i]);
        parseDataFromLine(datastream, x);
        parseDataFromLine(datastream, v);
        datastream >> m;

        ParticleParameters parameters(x, v, m, 0, 0);
        Particle newParticle = particleGenerator.generateParticle(parameters);
        particleContainer.addParticle(newParticle);
    }

    particleContainer.initializePairs();
    particleContainer.setVolumes();
    return particleContainer;
}

ParticleContainer FileReader::loadCuboid(const std::string &filepath) {
    ParticleContainer particleContainer;
    std::array<double, 3> llf, startV;
    std::array<size_t, 3> numParticles;
    double distance, mass, meanV;

    auto lines = readFileLines(filepath);
    int num_cuboids = std::stoi(lines[0]);
    std::cout << "num_cuboids: " << num_cuboids << std::endl;

    for (int i = 1; i < num_cuboids + 1; ++i) {
        std::istringstream datastream(lines[i]);
        parseDataFromLine(datastream, llf);
        parseDataFromLine(datastream, numParticles);
        datastream >> distance >> mass;
        parseDataFromLine(datastream, startV);
        datastream >> meanV;

        if (datastream.fail()) {
            std::cout << "Error reading file: unexpected data format on line " << i + 1 << std::endl;
            exit(-1);
        }

        CuboidParameters cuboidParams(llf, numParticles, distance, mass, startV, meanV);
        std::cout << "Generating cuboid with particle number: " << numParticles[0] << ", " << numParticles[1] << ", " << numParticles[2] << std::endl;
        particleGenerator.generateCuboid(cuboidParams, particleContainer);
        std::cout << "Generating cuboid completed" << std::endl;
        particleContainer.initializePairs();
    }

    return particleContainer;
}

// ------------------------------------------- Helper methods --------------------------------------------------
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
void parseDataFromLine(std::istringstream &datastream, std::array<T, N> &data) {
    for (auto &value: data) {
        datastream >> value;
    }
    if (datastream.fail()) {
        std::cout << "Error reading file: unexpected data format" << std::endl;
        exit(-1);
    }
}

/**
 * This method reads the file specified by the parameter 'filepath'
 * and returns only relevant lines (that are no comments) in the file as a vector strings.
 *
 * Moreover, this functions checks if the given "number of cuboid" in the input file is non-negative or not.
 *
 * @param filepath
 * @return vector of strings
 */
std::vector<std::string> readFileLines(const std::string &filepath) {
    std::vector<std::string> lines;
    std::ifstream input_file(filepath);
    std::string tmp_string;
    bool num_data_read = false;

    if (input_file.is_open()) {
        while (std::getline(input_file, tmp_string)) {
            if (!tmp_string.empty() && tmp_string[0] != '#') {
                if (!num_data_read) {
                    int num_data = std::stoi(tmp_string);
                    if (num_data < 0) {
                        std::cerr << "Error: Number of data sets cannot be negative." << std::endl;
                        exit(-1);
                    }

                    // Reserve space in the vector to avoid reallocations
                    lines.reserve(num_data + 1);
                    num_data_read = true;
                }

                lines.push_back(tmp_string);
            }
        }
    } else {
        std::cout << "Error: could not open file " << filepath << std::endl;
        exit(-1);
    }
    return lines;
}