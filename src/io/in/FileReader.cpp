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

FileReader::FileReader() = default;

FileReader::~FileReader() = default;

ParticleContainer FileReader::readParticleData(const std::string& filename) {
    ParticleContainer particleContainer;

    std::array<double, 3> x;
    std::array<double, 3> v;
    double m;
    int num_particles = 0;

    std::ifstream input_file(filename);
    std::string tmp_string;

    if (input_file.is_open()) {

        getline(input_file, tmp_string);
        std::cout << "Read line: " << tmp_string << std::endl;

        while (tmp_string.empty() or tmp_string[0] == '#') {
            getline(input_file, tmp_string);
            std::cout << "Read line: " << tmp_string << std::endl;
        }

        std::istringstream numstream(tmp_string);
        numstream >> num_particles;
        std::cout << "Reading " << num_particles << "." << std::endl;
        getline(input_file, tmp_string);
        std::cout << "Read line: " << tmp_string << std::endl;

        for (int i = 0; i < num_particles; i++) {
            std::istringstream datastream(tmp_string);
            for (auto &xj: x) {
                datastream >> xj;
            }
            for (auto &vj: v) {
                datastream >> vj;
            }
            if (datastream.eof()) {
                std::cout
                        << "Error reading file: eof reached unexpectedly reading from line "
                        << i << std::endl;
                exit(-1);
            }
            datastream >> m;
            particleContainer.addParticle(Particle(x, v, m, 0));

            getline(input_file, tmp_string);
            std::cout << "Read line: " << tmp_string << std::endl;
        }
        particleContainer.initializePairs();
        particleContainer.setVolumes();
    } else {
        std::cout << "Error: could not open file " << filename << std::endl;
        exit(-1);
    }
    return particleContainer;
}

// TODO
CuboidParameters FileReader::readCuboidParameters(const std::string& filepath) {
}
