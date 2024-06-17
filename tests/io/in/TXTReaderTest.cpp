//
// Created by Ujin on 12.05.2024.
//

#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

#include "../../../src/io/in/TXTReader.h"

namespace {
    const auto fileReader = std::make_unique<fileReaders::TXTReader>();
}

//Check if the lines are read correctly and wrong lines are ignored
TEST(FileReaderTest, readFileLinesBasicTest) {
    std::ofstream testfile("test_file.txt");
    testfile << "# This should be ignored\n"
             << "0\n"  // Data code for particles
             << "4\n"  // Number of data sets
             << "# This should be ignored\n"
             << "2\n" // Dimension of simulation
             << "Data Set 1\n"
             << "Data Set 2\n"
             << "Data Set 3\n";
    testfile.close();
    std::vector<std::string> lines = fileReader->readFileLines("test_file.txt");
    ASSERT_EQ(lines.size(), 6);
    EXPECT_EQ(lines[0], "0");
    EXPECT_EQ(lines[1], "4");
    EXPECT_EQ(lines[2], "2");
    EXPECT_EQ(lines[3], "Data Set 1");
    EXPECT_EQ(lines[4], "Data Set 2");
    EXPECT_EQ(lines[5], "Data Set 3");

    // Delete the temporary file
    std::remove("test_file.txt");
}

// Test case for reading particles from a file
TEST(ReadFileTest, ReadParticlesFromFile) {
    std::ofstream outfile("test_particles.txt");
    outfile << "0\n"  // Data code for particles
            << "4\n"  // Number of data sets
            << "2\n" // Dimension of simulation
            << "0.0 0.0 0.0      0.0 0.0 0.0     1.0\n"
            << "0.0 1.0 0.0     -1.0 0.0 0.0     3.0e-6\n"
            << "0.0 5.36 0.0    -0.425 0.0 0.0   9.55e-4\n"
            << "34.75 0.0 0.0    0.0 0.0296 0.0  1.0e-14\n";
    outfile.close();

    SimulationDataContainer simulationDataContainer = fileReader->readFile("test_particles.txt");
    ParticleContainer particleContainer = *simulationDataContainer.getParticleContainer();

    ASSERT_EQ(particleContainer.getSize(), 4);
    std::vector<Particle> container = particleContainer.getParticles();

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

    for (size_t i = 0; i < container.size(); ++i) {
        ASSERT_EQ(container[i].getX(), expectedPositions[i]);
        ASSERT_EQ(container[i].getV(), expectedVelocities[i]);
        ASSERT_EQ(container[i].getM(), expectedMasses[i]);
    }

    std::remove("test_particles.txt");
}

// Test case for reading cuboids from a file
TEST(ReadFileTest, ReadCuboidsFromFile) {
    std::ofstream outfile("test_cuboids.txt");
    outfile << "1\n"  // Data code for cuboids
            << "2\n"  // Number of data sets
            << "2\n" // Dimension of simulation
            << "0.0 0.0 0.0         2 2 1           1.0         1.0         0.0 0.0 0.0     0.1\n"
            << "-10.0 -10.0 0.0     3 3 1           1.0         1.0         0.0 -10.0 0.0   0.1\n";
    outfile.close();

    SimulationDataContainer simulationDataContainer = fileReader->readFile("test_cuboids.txt");
    ParticleContainer particleContainer = *simulationDataContainer.getParticleContainer();

    ASSERT_EQ(particleContainer.getSize(), 13);
    std::vector<Particle> particles = particleContainer.getParticles();

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

    std::remove("test_cuboids.txt");
}

// Test case for handling empty file
TEST(ReadFileTest, EmptyFile) {
    std::ofstream outfile("empty_file.txt");
    outfile.close();

    ASSERT_THROW(fileReader->readFile("empty_file.txt"), std::runtime_error);

    std::remove("empty_file.txt");
}

// Test case for FileReader::loadParticles method
TEST(FileReaderTest, LoadParticles) {
    std::vector<std::string> lines = {
            "4", // Number of particles
            "2", // Dimension of simulation
            "0.0 0.0 0.0   0.0 0.0 0.0   1.0",
            "0.0 1.0 0.0  -1.0 0.0 0.0   3.0e-6",
            "0.0 5.36 0.0 -0.425 0.0 0.0 9.55e-4",
            "34.75 0.0 0.0 0.0 0.0296 0.0 1.0e-14"
    };

    ParticleContainer particleContainer;
    fileReader->loadParticles(lines, particleContainer);

    ASSERT_EQ(particleContainer.getSize(), 4);
    std::vector<Particle> particles = particleContainer.getParticles();

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

    for (size_t i = 0; i < particles.size(); ++i) {
        std::array<double, 3> xPos = particles[i].getX();
        std::array<double, 3> vPos = particles[i].getV();
        double mass = particles[i].getM();

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
            "2", // Dimension of simulation
            "0.0 0.0 0.0   2 2 1   1.0 1.0   0.0 0.0 0.0   0.1",
            "-10.0 -10.0 0.0   3 3 1   1.0 1.0   0.0 -10.0 0.0   0.1"
    };

    ParticleContainer particleContainer;
    fileReader->loadCuboids(lines, particleContainer);

    ASSERT_EQ(particleContainer.getSize(), 13);
    std::vector<Particle> particles = particleContainer.getParticles();

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

    for (size_t i = 0; i < particles.size(); ++i) {
        std::array<double, 3> xPos = particles[i].getX();
        double mass = particles[i].getM();

        ASSERT_EQ(xPos, expectedPositions[i]);
        ASSERT_EQ(mass, expectedMass);
    }
}

// Test case for FileReader::loadDiscs method
TEST(FileReaderTest, LoadDiscs) {
    std::vector<std::string> lines = {
            "1", // Number of discs
            "2", // Dimension of simulation
            "0.0 0.0 0.0   0.0 0.0 0.0   2   1.0   1.0   2" // Disc parameters
    };

    ParticleContainer particleContainer;
    fileReader->loadDiscs(lines, particleContainer);

    ASSERT_EQ(particleContainer.getSize(), 13); // 13 particles for a disc with radius 2 in 2D
    std::vector<Particle> particles = particleContainer.getParticles();

    double expectedMass = 1.0;
    std::array<double, 3> expectedVelocity = {0.0, 0.0, 0.0};

    for (auto& particle : particles) {
        double distanceFromCenter = std::sqrt(std::pow(particle.getX()[0], 2) + std::pow(particle.getX()[1], 2));
        ASSERT_LE(distanceFromCenter, 2.0); // All particles should be within the disc's radius
        ASSERT_EQ(particle.getV(), expectedVelocity);
        ASSERT_EQ(particle.getM(), expectedMass);
    }
}