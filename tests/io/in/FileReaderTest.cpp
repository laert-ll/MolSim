//
// Created by Ujin on 12.05.2024.
//

#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

#include "../../../src/io/in/TXTReader.h"

//Check if the lines are read correctly and wrong lines are ignored
TEST(FileReaderTest, readFileLinesBasicTest) {
    fileReaders::TXTReader fileReader;
    std::ofstream testfile("test_file.txt");
    testfile << "3\n"
             << "# This should be ignored\n"
             << "Data Set 1\n"
             << "Data Set 2\n"
             << "Data Set 3\n";
    testfile.close();
    std::vector<std::string> lines = fileReaders::TXTReader::readFileLines("test_file.txt");
    ASSERT_EQ(lines.size(), 4);
    EXPECT_EQ(lines[1], "Data Set 1");
    EXPECT_EQ(lines[2], "Data Set 2");
    EXPECT_EQ(lines[3], "Data Set 3");

    // Delete the temporary file
    std::remove("test_file.txt");
}

// Test case for reading particles from a file
TEST(ReadFileTest, ReadParticlesFromFile) {
    // Create a temporary file with particle data
    std::ofstream outfile("test_particles.txt");
    outfile << "0\n"  // Data code for particles
            << "4\n"  // Number of data sets
            << "0.0 0.0 0.0      0.0 0.0 0.0     1.0\n"
            << "0.0 1.0 0.0     -1.0 0.0 0.0     3.0e-6\n"
            << "0.0 5.36 0.0    -0.425 0.0 0.0   9.55e-4\n"
            << "34.75 0.0 0.0    0.0 0.0296 0.0  1.0e-14\n";
    outfile.close();

    fileReaders::TXTReader fileReader;
    ParticleContainer particleContainer = fileReader.readFile("test_particles.txt");

    // Check if the particles are loaded correctly
    ASSERT_EQ(particleContainer.getSize(), 4);
    std::vector<Particle> container = particleContainer.getParticles();

    // Define expected positions, velocities, and masses
    std::array<std::array<double, 3>, 4> expectedPositions = {
            {{0.0, 0.0, 0.0},
             {0.0, 1.0, 0.0},
             {0.0, 5.36, 0.0},
             {34.75, 0.0, 0.0}}
    };

    std::array<std::array<double, 3>, 4> expectedVelocities = {
            {{0.0, 0.0, 0.0},
             {-1.0, 0.0, 0.0},
             {-0.425, 0.0, 0.0},
             {0.0, 0.0296, 0.0}}
    };

    std::array<double, 4> expectedMasses = {1.0, 3.0e-6, 9.55e-4, 1.0e-14};

    // Loop through particles and perform assertions
    for (size_t i = 0; i < container.size(); ++i) {
        ASSERT_EQ(container[i].getX(), expectedPositions[i]);
        ASSERT_EQ(container[i].getV(), expectedVelocities[i]);
        ASSERT_EQ(container[i].getM(), expectedMasses[i]);
    }

    // Delete the temporary file
    std::remove("test_particles.txt");
}

// Test case for reading cuboids from a file
TEST(ReadFileTest, ReadCuboidsFromFile) {
    // Create a temporary file with cuboid data
    std::ofstream outfile("test_cuboids.txt");
    outfile << "1\n"  // Data code for cuboids
            << "2\n"  // Number of data sets
            << "0.0 0.0 0.0         2 2 1           1.0         1.0         0.0 0.0 0.0     0.1\n"
            << "-10.0 -10.0 0.0     3 3 1           1.0         1.0         0.0 -10.0 0.0   0.1\n";
    outfile.close();

    // Read cuboid data from the file
    ParticleContainer particleContainer = fileReaders::TXTReader::readFile("test_particles.txt");

    // Check if the cuboids are loaded correctly
    ASSERT_EQ(particleContainer.getSize(), 13);
    std::vector<Particle> particles = particleContainer.getParticles();

    // Position check & Mass check
    double mass = 1.0;
    std::array<std::array<double, 3>, 13> expectedPositions = {
            {{0.0, 0.0, 0.0},
             {0.0, 1.0, 0.0},
             {1.0, 0.0, 0.0},
             {1.0, 1.0, 0.0},
             {-10.0, -10.0, 0.0},
             {-10.0, -9.0, 0.0},
             {-10.0, -8.0, 0.0},
             {-9.0, -10.0, 0.0},
             {-9.0, -9.0, 0.0},
             {-9.0, -8.0, 0.0},
             {-8.0, -10.0, 0.0},
             {-8.0, -9.0, 0.0},
             {-8.0, -8.0, 0.0}}
    };

    for (size_t i = 0; i < particles.size(); ++i) {
        ASSERT_EQ(particles[i].getX(), expectedPositions[i]);
        ASSERT_EQ(particles[i].getM(), mass);
    }

    // Delete the temporary file
    std::remove("test_cuboids.txt");
}

// Test case for handling empty file
TEST(ReadFileTest, EmptyFile) {
    // Create an empty temporary file
    std::ofstream outfile("empty_file.txt");
    outfile.close();

    // Test whether the method throws an exception for an empty file
    fileReaders::TXTReader fileReader;
    ASSERT_THROW(fileReader.readFile("empty_file.txt"), std::runtime_error);

    // Delete the temporary file
    std::remove("empty_file.txt");
}

// Test case for FileReader::loadParticles method
TEST(FileReaderTest, LoadParticles) {
    // Prepare input data
    std::vector<std::string> lines = {
            "4", // Number of particles
            "0.0 0.0 0.0   0.0 0.0 0.0   1.0",
            "0.0 1.0 0.0  -1.0 0.0 0.0   3.0e-6",
            "0.0 5.36 0.0 -0.425 0.0 0.0 9.55e-4",
            "34.75 0.0 0.0 0.0 0.0296 0.0 1.0e-14"
    };

    // Create a ParticleContainer object
    ParticleContainer particleContainer;
    fileReaders::TXTReader::loadParticles(lines, particleContainer);

    // Check if the particles are loaded correctly
    ASSERT_EQ(particleContainer.getSize(), 4);
    std::vector<Particle> particles = particleContainer.getParticles();

    // Check particle parameters
    std::array<std::array<double, 3>, 4> expectedPositions = {
            {{0.0, 0.0, 0.0},
             {0.0, 1.0, 0.0},
             {0.0, 5.36, 0.0},
             {34.75, 0.0, 0.0}}
    };

    std::array<std::array<double, 3>, 4> expectedVelocities = {
            {{0.0, 0.0, 0.0},
             {-1.0, 0.0, 0.0},
             {-0.425, 0.0, 0.0},
             {0.0, 0.0296, 0.0}}
    };

    std::array<double, 4> expectedMasses = {1.0, 3.0e-6, 9.55e-4, 1.0e-14};

    // Loop through particles and perform assertions
    for (size_t i = 0; i < particles.size(); ++i) {
        // Get particle parameters
        std::array<double, 3> xPos = particles[i].getX();
        std::array<double, 3> vPos = particles[i].getV();
        double mass = particles[i].getM();

        // Compare with expected values
        ASSERT_EQ(xPos, expectedPositions[i]);
        ASSERT_EQ(vPos, expectedVelocities[i]);
        ASSERT_EQ(mass, expectedMasses[i]);
    }
}

// Test case for FileReader::loadCuboids method
TEST(FileReaderTest, LoadCuboids) {
    // Prepare input data
    std::vector<std::string> lines = {
            "2", // Number of cuboids
            "0.0 0.0 0.0   2 2 1   1.0 1.0   0.0 0.0 0.0   0.1",
            "-10.0 -10.0 0.0   3 3 1   1.0 1.0   0.0 -10.0 0.0   0.1"
    };

    ParticleContainer particleContainer;
    fileReaders::TXTReader::loadCuboids(lines, particleContainer);

    // Check if the particles are loaded correctly
    ASSERT_EQ(particleContainer.getSize(), 13);
    std::vector<Particle> particles = particleContainer.getParticles();

    // Define expected positions and mass
    double expectedMass = 1.0;
    std::array<std::array<double, 3>, 13> expectedPositions = {
            {{0.0, 0.0, 0.0},
             {0.0, 1.0, 0.0},
             {1.0, 0.0, 0.0},
             {1.0, 1.0, 0.0},
             {-10.0, -10.0, 0.0},
             {-10.0, -9.0, 0.0},
             {-10.0, -8.0, 0.0},
             {-9.0, -10.0, 0.0},
             {-9.0, -9.0, 0.0},
             {-9.0, -8.0, 0.0},
             {-8.0, -10.0, 0.0},
             {-8.0, -9.0, 0.0},
             {-8.0, -8.0, 0.0}}
    };

    // Loop through particles and perform assertions
    for (size_t i = 0; i < particles.size(); ++i) {
    // Get particle parameters
        std::array<double, 3> xPos = particles[i].getX();
        double mass = particles[i].getM();

        // Compare with expected values
        ASSERT_EQ(xPos, expectedPositions[i]);
        ASSERT_EQ(mass, expectedMass);
    }
}