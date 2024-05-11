/*
 * FileReader.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "FileReader.h"
#include "spdlog/spdlog.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

template<typename T, size_t N>
void parseDataFromLine(std::istringstream &datastream, std::array<T, N> &data);

std::vector<std::string> readFileLines(const std::string &filepath);

ParticleContainer FileReader::readFile(const std::string &filepath) {
    auto lines = readFileLines(filepath);

    // Check if there are lines in the file
    if (lines.empty()) {
        throw std::runtime_error("File is empty: " + filepath);
    }

    // Parse the data code
    int dataCode;
    try {
        dataCode = std::stoi(lines[0]);
        // Remove the first element of lines
        lines.erase(lines.begin());
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error(
                "Invalid data code in file '" + filepath + "': " + e.what() + ". Data code must be an integer.");
    } catch (const std::out_of_range &e) {
        throw std::runtime_error(
                "Data code out of range in file '" + filepath + "': " + e.what() + ". Data code must be an integer.");
    }

    // Log the data code
    SPDLOG_INFO("Data Code of file '{}': {}", filepath, dataCode);
    // Load particles or cuboid based on data code
    ParticleContainer particleContainer;
    switch (dataCode) {
        case 0:
            loadParticles(lines, particleContainer);
            break;
        case 1:
            loadCuboids(lines, particleContainer);
            break;
        default:
            throw std::runtime_error(
                    "Invalid data code in file '" + filepath + "': Only data codes 0 and 1 are supported.");

    }

    return particleContainer;
}

void FileReader::loadParticles(const std::vector<std::string> &lines, ParticleContainer &particleContainer) {
    std::array<double, 3> x{}, v{};
    double m;

    int num_particles = std::stoi(lines[0]);

    for (int i = 1; i < num_particles + 1; ++i) {
        std::istringstream datastream(lines[i]);
        parseDataFromLine(datastream, x);
        parseDataFromLine(datastream, v);
        datastream >> m;

        ParticleParameters parameters(x, v, m, 0, 0);
        Particle newParticle = ParticleGenerator::generateParticle(parameters);
        particleContainer.addParticle(newParticle);
    }

    particleContainer.initializePairs();
    particleContainer.setVolumes();
}

void FileReader::loadCuboids(const std::vector<std::string> &lines, ParticleContainer &particles) {
    std::array<double, 3> llf{}, startV{};
    std::array<size_t, 3> numParticles{};
    double distance, mass, meanV;

    int num_cuboids = std::stoi(lines[0]);
    SPDLOG_INFO("num_cuboids: {}", num_cuboids);

    for (int i = 1; i < num_cuboids + 1; ++i) {
        std::istringstream datastream(lines[i]);
        parseDataFromLine(datastream, llf);
        parseDataFromLine(datastream, numParticles);
        datastream >> distance >> mass;
        parseDataFromLine(datastream, startV);
        datastream >> meanV;

        if (datastream.fail()) {
            SPDLOG_ERROR("Error reading file: unexpected data format on line {}", i + 1);
            exit(-1);
        }

        CuboidParameters cuboidParams(llf, numParticles, distance, mass, startV, meanV);
        SPDLOG_INFO("Generating cuboid with particle number: {}, {}, {}", numParticles[0], numParticles[1],
                    numParticles[2]);
        ParticleGenerator::generateCuboid(cuboidParams, particles);
        SPDLOG_INFO("Generating cuboid completed");
        particles.initializePairs();
    }
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
        SPDLOG_ERROR("Error reading file: unexpected data format");
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
                        SPDLOG_ERROR("Error: Number of data sets cannot be negative.");
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
        SPDLOG_ERROR("Error: could not open file {}", filepath);
        exit(-1);
    }
    return lines;
}