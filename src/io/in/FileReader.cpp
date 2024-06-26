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

ParticleContainer FileReader::readFile(const std::string &filepath) {
    auto lines = readFileLines(filepath);

    // Check if there are lines in the file
    if (lines.empty()) {
        SPDLOG_ERROR("File is empty: ", filepath);
        throw std::runtime_error("File is empty: " + filepath);
    }

    // Validate the header lines
    validateHeaderLines(lines);

    // Parse the data code
    int dataCode = std::stoi(lines[0]);
    lines.erase(lines.begin());

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
        case 2:
            loadDiscs(lines, particleContainer);
            break;
        case 3:
            loadCells(lines, particleContainer);
            break;
        default:
            SPDLOG_ERROR("Invalid data code in file '", filepath + "': Only data codes 0 and 1 are supported.");
            throw std::runtime_error(
                    "Invalid data code in file '" + filepath + "': Only data codes 0 and 1 are supported.");
    }

    return particleContainer;
}

void FileReader::loadParticles(const std::vector<std::string> &lines, ParticleContainer &particleContainer) {
    std::array<double, 3> x{}, v{};
    double m;

    int num_particles = std::stoi(lines[0]);
    int dimension = std::stoi(lines[1]);
    SPDLOG_DEBUG("Number of particles to load: {}", num_particles);
    SPDLOG_DEBUG("Dimension of simulation: {}", dimension);

    for (int i = 2; i < num_particles + 2; ++i) {
        std::istringstream datastream(lines[i]);
        parseDataFromLine(datastream, x);
        parseDataFromLine(datastream, v);
        datastream >> m;

        ParticleParameters parameters(x, v, m, 0, 0, dimension);
        Particle newParticle = ParticleGenerator::generateParticle(parameters);
        particleContainer.addParticle(newParticle);
    }

    particleContainer.initializePairs();
    particleContainer.setVolumes();
}

void FileReader::loadCuboids(const std::vector<std::string> &lines, ParticleContainer &particles) {
    SPDLOG_INFO("Starting to load cuboids...");
    std::array<double, 3> llf{}, startV{};
    std::array<size_t, 3> numParticles{};
    double distance, mass, meanV;

    int num_cuboids = std::stoi(lines[0]);
    int dimension = std::stoi(lines[1]);
    SPDLOG_DEBUG("Number of cuboids to load: {}", num_cuboids);
    SPDLOG_DEBUG("Dimension of simulation: {}", dimension);

    for (int i = 2; i < num_cuboids + 2; ++i) {
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

        CuboidParameters cuboidParams(llf, numParticles, distance, mass, startV, meanV, dimension);
        ParticleGenerator::generateCuboid(cuboidParams, particles);
        SPDLOG_DEBUG("Completed generating cuboid {}", i);
    }
    particles.initializePairs();
    SPDLOG_INFO("Finished loading cuboids!");
}


void FileReader::loadDiscs(const std::vector<std::string> &lines, ParticleContainer &particles) {
    SPDLOG_INFO("Starting to load discs...");
    std::array<double, 3> center{}, startV{};
    int numParticlesAlongRadius;
    double distance, mass;

    int num_discs = std::stoi(lines[0]);
    int dimension = std::stoi(lines[1]);
    SPDLOG_DEBUG("Number of discs to load: {}", num_discs);
    SPDLOG_DEBUG("Dimension of simulation: {}", dimension);

    for (int i = 2; i < num_discs + 2; ++i) {
        std::istringstream datastream(lines[i]);
        parseDataFromLine(datastream, center);
        parseDataFromLine(datastream, startV);
        datastream >> numParticlesAlongRadius >> distance >> mass;

        if (datastream.fail()) {
            SPDLOG_ERROR("Error reading file: unexpected data format on line {}", i + 1);
            exit(-1);
        }

        DiscParameters discParams(center, startV, numParticlesAlongRadius, distance, mass, dimension);
        ParticleGenerator::generateDisc(discParams, particles);
        SPDLOG_DEBUG("Completed generating disc {}", i);
        particles.initializePairs();
    }
    SPDLOG_INFO("Finished loading discs!");
}

void FileReader::loadCells(const std::vector<std::string> &lines, ParticleContainer &particles) {
    SPDLOG_INFO("Starting to load cuboids...");
    std::array<double, 3> llf{}, startV{};
    std::array<size_t, 3> numParticles{};
    double distance, mass, meanV;

    int num_cuboids = std::stoi(lines[0]);
    int dimension = std::stoi(lines[1]);
    double width = std::stoi(lines[2]);
    double height = std::stoi(lines[3]);
    double cutoff_radius = std::stoi(lines[4]);
    SPDLOG_DEBUG("Number of cuboids to load: {}", num_cuboids);
    SPDLOG_DEBUG("Dimension of simulation: {}", dimension);
    SPDLOG_DEBUG("Domain width: {}", width);
    SPDLOG_DEBUG("Domain height: {}", height);
    SPDLOG_DEBUG("Cutoff radius: {}", cutoff_radius);

    std::array<double, 2> cell_size = {cutoff_radius, cutoff_radius};

    for (double x = 0; x < (width / cutoff_radius); ++x) {
        for (double y = 0; y < (height / cutoff_radius); ++y) {
            std::array<double, 2> start_coordinates = {x * cell_size[0], 
                                                       y * cell_size[1]};
            std::array<double, 2> end_coordinates = {start_coordinates[0] + cutoff_radius, 
                                                     start_coordinates[1] + cutoff_radius};
            particles.addCell(start_coordinates, end_coordinates);
            SPDLOG_DEBUG("Added cell with start_coordinates: ({}, {}) and end_coordinates: ({}, {})",
                        start_coordinates[0], start_coordinates[1], end_coordinates[0], end_coordinates[1]);
        }
    }

    particles.initializeNeighboringCells();

    for (int i = 5; i < num_cuboids + 5; ++i) {
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

        CuboidParameters cuboidParams(llf, numParticles, distance, mass, startV, meanV, dimension);
        ParticleGenerator::generateCuboid(cuboidParams, particles);
        SPDLOG_DEBUG("Completed generating cuboid {}", i);
    }
    particles.arrangeCells();
    SPDLOG_INFO("Finished loading cuboids!");
}

// ------------------------------------------- Helper methods --------------------------------------------------
const std::set<int> FileReader::allowedDataCodes = {0, 1, 2, 3};
const std::set<int> FileReader::allowedDimensions = {2, 3};

template<typename T, size_t N>
void FileReader::parseDataFromLine(std::istringstream &datastream, std::array<T, N> &data) {
    for (auto &value: data) {
        datastream >> value;
    }
    if (datastream.fail()) {
        SPDLOG_ERROR("Error reading file: unexpected data format");
        exit(-1);
    }
}

std::vector<std::string> FileReader::readFileLines(const std::string &filepath) {
    std::vector<std::string> lines;
    std::ifstream input_file(filepath);
    std::string tmp_string;
    bool data_code_read = false;
    bool num_data_read = false;
    bool dimension_read = false;

    if (input_file.is_open()) {
        while (std::getline(input_file, tmp_string)) {
            // Ignore comment lines
            if (!tmp_string.empty() && tmp_string[0] == '#') {
                continue;
            }

            // Read and validate the data code
            if (!data_code_read) {
                int data_code = std::stoi(tmp_string);
                if (allowedDataCodes.find(data_code) == allowedDataCodes.end()) {
                    SPDLOG_ERROR("Error: Invalid data code {}. Only 0 and 1 are allowed.", data_code);
                    exit(-1);
                }
                data_code_read = true;
            }

                // Read and validate the number of data sets
            else if (!num_data_read) {
                int num_data = std::stoi(tmp_string);
                if (num_data < 0) {
                    SPDLOG_ERROR("Error: Number of data sets cannot be negative.");
                    exit(-1);
                }
                num_data_read = true;
            }

                // Read and validate the dimension
            else if (!dimension_read) {
                int dimension = std::stoi(tmp_string);
                if (allowedDimensions.find(dimension) == allowedDimensions.end()) {
                    SPDLOG_ERROR("Error: Invalid dimension {}. Only 2 or 3 are allowed.", dimension);
                    exit(-1);
                }
                dimension_read = true;
            }

            // Add the line to the vector
            lines.push_back(tmp_string);
        }
    } else {
        SPDLOG_ERROR("Error: could not open file {}", filepath);
        exit(-1);
    }
    return lines;
}

void FileReader::validateHeaderLines(const std::vector<std::string> &lines) {
    bool data_code_read = false;
    bool num_datasets_read = false;

    if (lines.size() < 3) {
        SPDLOG_ERROR("Error: File does not contain enough header lines. Expected 3 header lines, but found {}.",
                     lines.size());
        exit(-1);
    }

    for (const auto &line: lines) {
        // Read and validate the data code
        if (!data_code_read) {
            int data_code = std::stoi(line);
            if (allowedDataCodes.find(data_code) == allowedDataCodes.end()) {
                SPDLOG_ERROR("Error: Invalid data code {}. Only 0 and 1 are allowed.", data_code);
                exit(-1);
            }
            data_code_read = true;
        }

            // Read and validate the number of data sets
        else if (!num_datasets_read) {
            int num_data = std::stoi(line);
            if (num_data < 0) {
                SPDLOG_ERROR("Error: Number of data sets cannot be negative.");
                exit(-1);
            }
            num_datasets_read = true;
        }

            // Read and validate the dimension
        else {
            int dimension = std::stoi(line);
            if (allowedDimensions.find(dimension) == allowedDimensions.end()) {
                SPDLOG_ERROR("Error: Invalid dimension {}. Only 2 or 3 are allowed.", dimension);
                exit(-1);
            }
            return;
        }
    }
}
