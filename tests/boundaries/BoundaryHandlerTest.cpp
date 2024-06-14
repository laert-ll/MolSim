//
// Created by U-jin Hong on 04.06.24.
//

#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

#include "boundaries/BoundaryHandler.h"
#include "calculators/LJCalculator.h"
#include "io/in/FileReader.h"
#include "io/in/TXTReader.h"
#include "io/in/XMLReader.h"

// Helper function to compare two std::array<double, 3> with a given tolerance
bool arraysNear(const std::array<double, 3> &arr1, const std::array<double, 3> &arr2, double tolerance) {
    for (size_t i = 0; i < arr1.size(); ++i) {
        if (std::fabs(arr1[i] - arr2[i]) > tolerance) {
            return false;
        }
    }
    return true;
}

// Custom Google Test macro for comparing std::array<double, 3>
#define ASSERT_ARRAYS_NEAR(arr1, arr2, tolerance) \
    ASSERT_PRED3(arraysNear, arr1, arr2, tolerance)

namespace boundaries {
// Testing Particles moving against every reflecting boundary
// Check if the forces after reflection are correct
    TEST(BoundaryHandlerTest, BasicReflection) {
        SPDLOG_INFO("Testing Reflections...");
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        std::array<double, 2> domain = {20.0, 20.0};
        std::unique_ptr<calculators::Calculator> calculator = std::make_unique<calculators::LJCalculator>(3.0);
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator.get(), 1.0};
        std::ofstream outfile("particles_near_reflecting_boundary.txt");
        outfile << "0\n"  // Data code for Particles
                << "4\n"  // Number of data sets
                << "2\n"  // Dimension of simulation
                << "10.0 0.5 0.0     0.0 3.0 0.0      1.0\n" // Bottom
                << "10.0 19.5 0.0    0.0 3.0 0.0      1.0\n" // Top
                << "0.5 10.0 0.0     -3.0 0.0 0.0     1.0\n" // Left
                << "19.5 10.0 0.0    3.0 0.0 0.0      1.0\n";// Right
        outfile.close();

        // Read cuboid data from the file
        ParticleContainer container = fileReaders::TXTReader::readFile("particles_near_reflecting_boundary.txt");
        std::remove("particles_near_reflecting_boundary");

        // Check if Force of all Particles is zero
        std::array<double, 3> zero{0.0, 0.0, 0.0};
        for (Particle &p: container) {
            ASSERT_EQ(p.getF(), zero);
        }
        std::vector<std::array<double, 3>> expectedReflectedForces{{0.0,    120.0,  0.0},
                                                                   {0.0,    -120.0, 0.0},
                                                                   {120.0,  0.0,    0.0},
                                                                   {-120.0, 0.0,    0.0}};
        handler.preProcessBoundaries(container);
        std::vector<Particle> particles = container.getParticles();
        for (int i = 0; i < 4; i++) {
            ASSERT_ARRAYS_NEAR(particles[i].getF(), expectedReflectedForces[i], 1e-6);
        }
    }

// Testing Particles moving against every reflecting boundary
// Check if the forces after reflection are correct
    TEST(BoundaryHandlerTest, CornerReflection) {
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        std::array<double, 2> domain = {20.0, 20.0};
        std::unique_ptr<calculators::Calculator> calculator = std::make_unique<calculators::LJCalculator>(3.0);
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator.get(), 1.0};
        std::ofstream outfile("particles_near_reflecting_boundary.txt");
        outfile << "0\n"  // Data code for Particles
                << "4\n"  // Number of data sets
                << "2\n"  // Dimension of simulation
                << "0.5 0.5 0.0     -1000.0 -3.0 0.0     1.0\n" // Bottom Left
                << "0.5 19.5 0.0    -1000.0 3.0 0.0      1.0\n" // Top Left
                << "19.5 0.5 0.0     1000.0 -3.0 0.0     1.0\n" // Bottom Right
                << "19.5 19.5 0.0    1000.0 3.0 0.0      1.0\n";// Top Right
        outfile.close();

        // Read cuboid data from the file
        ParticleContainer container = fileReaders::TXTReader::readFile("particles_near_reflecting_boundary.txt");
        std::remove("particles_near_reflecting_boundary");

        // Check if Force of all Particles is zero
        std::array<double, 3> zero{0.0, 0.0, 0.0};
        for (Particle &p: container) {
            ASSERT_EQ(p.getF(), zero);
        }
        std::vector<std::array<double, 3>> expectedReflectedForces{{120.0,  120.0,  0},
                                                                   {120.0,  -120.0, 0},
                                                                   {-120.0, 120.0,  0},
                                                                   {-120.0, -120.0, 0}};
        handler.preProcessBoundaries(container);
        std::vector<Particle> particles = container.getParticles();
        for (int i = 0; i < 4; i++) {
            ASSERT_ARRAYS_NEAR(particles[i].getF(), expectedReflectedForces[i], 1e-6);
        }
    }


    TEST(BoundaryHandlerTest, BasicOutflow) {
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        boundaryMap.emplace(boundaries::BoundaryDirection::LEFT, boundaries::BoundaryType::OUTFLOW);
        boundaryMap.emplace(boundaries::BoundaryDirection::RIGHT, boundaries::BoundaryType::OUTFLOW);
        boundaryMap.emplace(boundaries::BoundaryDirection::BOTTOM, boundaries::BoundaryType::OUTFLOW);
        boundaryMap.emplace(boundaries::BoundaryDirection::TOP, boundaries::BoundaryType::OUTFLOW);

        std::array<double, 2> domain = {20.0, 20.0};
        std::unique_ptr<calculators::Calculator> calculator = std::make_unique<calculators::LJCalculator>(3.0);
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator.get(), 1.0};
        std::ofstream outfile("particles_near_reflecting_boundary.txt");
        outfile << "0\n"  // Data code for Particles
                << "4\n"  // Number of data sets
                << "2\n"  // Dimension of simulation
                << "10.0 0.5 0.0     0.0 -500.0 0.0     1.0\n"
                << "10.0 19.5 0.0    0.0 500.0 0.0      1.0\n"
                << "0.5 10.0 0.0     -1000.0 0.0 0.0     1.0\n"
                << "19.5 10.0 0.0    1000.0 0.0 0.0      1.0\n";
        outfile.close();

        // Read cuboid data from the file
        ParticleContainer container = fileReaders::TXTReader::readFile("particles_near_reflecting_boundary.txt");
        std::remove("particles_near_reflecting_boundary");

        // Check if Force of all Particles is zero
        std::array<double, 3> zero{0.0, 0.0, 0.0};
        for (Particle &p: container) {
            ASSERT_EQ(p.getF(), zero);
        }
        // First timestep - The faster two particles should be deleted on the left/right
        handler.preProcessBoundaries(container);
        calculator->calculate(container, 0.0005);
        handler.postProcessBoundaries(container);
        ASSERT_EQ(container.getSize(), 2);
        // Second timestep - The two slower particles get deleted on the bottom and top
        handler.preProcessBoundaries(container);
        calculator->calculate(container, 0.0005);
        handler.postProcessBoundaries(container);
        ASSERT_EQ(container.getSize(), 0);
    }

    // Check the Behaviour of two reflecting boundaries top and left, two outflow boundaries bottom and right
    TEST(BoundaryHandlerTest, MixedBoundaries) {
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        boundaryMap.emplace(boundaries::BoundaryDirection::BOTTOM, boundaries::BoundaryType::OUTFLOW);
        boundaryMap.emplace(boundaries::BoundaryDirection::RIGHT, boundaries::BoundaryType::OUTFLOW);

        std::array<double, 2> domain = {20.0, 20.0};
        std::unique_ptr<calculators::Calculator> calculator = std::make_unique<calculators::LJCalculator>(3.0);
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator.get(), 1.0};
        std::ofstream outfile("particles_near_reflecting_boundary.txt");
        outfile << "0\n"  // Data code for Particles
                << "8\n"  // Number of data sets
                << "2\n"  // Dimension of simulation
                << "10.0 0.5 0.0     0.0 -300.0 0.0     1.0\n" // Bottom - Slow
                << "10.0 19.5 0.0    0.0 300.0 0.0      1.0\n" // Top
                << "0.5 10.0 0.0     -300.0 0.0 0.0     1.0\n" // Left - Slow
                << "19.5 10.0 0.0    1000.0 0.0 0.0      1.0\n" // Right
                << "0.5 0.5 0.0     -300.0 -300.0 0.0  1.0\n" // Bottom Left - Slow
                << "0.5 19.5 0.0    -300.0 300.0 0.0      1.0\n" // Top Left - Slow
                << "19.5 0.5 0.0     1000.0 -300.0 0.0     1.0\n" // Bottom Right
                << "19.5 19.5 0.0    1000.0 300.0 0.0      1.0\n";// Top Right
        outfile.close();

        // Read cuboid data from the file
        ParticleContainer container = fileReaders::TXTReader::readFile("particles_near_reflecting_boundary.txt");
        std::remove("particles_near_reflecting_boundary");

        // Check if Force of all Particles is zero
        std::array<double, 3> zero{0.0, 0.0, 0.0};
        for (Particle &p: container) {
            ASSERT_EQ(p.getF(), zero);
        }
        handler.preProcessBoundaries(container);
        calculator->calculate(container, 0.0005);
        handler.postProcessBoundaries(container);
        std::vector<Particle> particles = container.getParticles();
        ASSERT_EQ(container.getSize(), 5);
        //First iteration
        std::vector<std::array<double, 3>> expectedForces{{0.0,   0.0,    0.0},
                                                          {0.0,   -120.0, 0.0},
                                                          {120.0, 0.0,    0.0},
                                                          {120.0, 0.0,    0.0},
                                                          {120.0, -120.0, 0.0}};
        std::vector<std::array<double, 3>> expectedPositions{{10.0, 0.35,  0.0},
                                                             {10.0, 19.65, 0.0},
                                                             {0.35, 10.0,  0.0},
                                                             {0.35, 0.35,  0.0},
                                                             {0.35, 19.65, 0.0}};
        for (int i = 0; i < 5; i++) {
            ASSERT_ARRAYS_NEAR(particles[i].getOldF(), expectedForces[i], 1e-6);
            ASSERT_ARRAYS_NEAR(particles[i].getX(), expectedPositions[i], 1e-6);
        }
        for (int i = 0; i < 3; i++) {
            handler.preProcessBoundaries(container);
            calculator->calculate(container, 0.0005);
            handler.postProcessBoundaries(container);
        }
        expectedForces.clear();
        expectedPositions.clear();
        particles.clear();
        particles = container.getParticles();
        ASSERT_EQ(container.getSize(), 3);
        expectedForces = {{0.0,     -20000.0, 0.0},
                          {20000.0, 0.0,      0.0},
                          {20000.0, -20000.0, 0.0}};
        expectedPositions = {{10.0,                 20.092454999999998, 0.0},
                             {-0.09245500000000006, 10.0,               0.0},
                             {-0.09245500000000006, 20.092454999999998, 0.0}};
        for (int i = 0; i < 3; i++) {
            ASSERT_ARRAYS_NEAR(particles[i].getOldF(), expectedForces[i], 1e-6);
            ASSERT_ARRAYS_NEAR(particles[i].getX(), expectedPositions[i], 1e-6);
        }
    }

    TEST(BoundaryHandlerTest, PeriodicBoundaries) {
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        boundaryMap.emplace(boundaries::BoundaryDirection::LEFT, boundaries::BoundaryType::OUTFLOW);
        boundaryMap.emplace(boundaries::BoundaryDirection::RIGHT, boundaries::BoundaryType::OUTFLOW);
        boundaryMap.emplace(boundaries::BoundaryDirection::BOTTOM, boundaries::BoundaryType::OUTFLOW);
        boundaryMap.emplace(boundaries::BoundaryDirection::TOP, boundaries::BoundaryType::OUTFLOW);

        std::array<double, 2> domain = {20.0, 20.0};
        std::unique_ptr<calculators::Calculator> calculator = std::make_unique<calculators::LJCalculator>(3.0);
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator.get(), 1.0};
        std::ofstream outfile("particles_near_reflecting_boundary.txt");
        outfile << "0\n"  // Data code for Particles
                << "4\n"  // Number of data sets
                << "2\n"  // Dimension of simulation
                << "15.0 0.5 0.0     0.0 -500.0 0.0     1.0\n"
                << "5.0 19.5 0.0    0.0 500.0 0.0      1.0\n"
                << "0.5 5.0 0.0     -1000.0 0.0 0.0     1.0\n"
                << "19.5 15.0 0.0    1000.0 0.0 0.0      1.0\n";
        outfile.close();

        // Read cuboid data from the file
        ParticleContainer container = fileReaders::TXTReader::readFile("particles_near_reflecting_boundary.txt");
        std::remove("particles_near_reflecting_boundary");

        // Check if Force of all Particles is zero
        std::array<double, 3> zero{0.0, 0.0, 0.0};
        for (Particle &p: container) {
            ASSERT_EQ(p.getF(), zero);
        }
        // First timestep - The faster two particles should be deleted on the left/right
        handler.preProcessBoundaries(container);
        calculator->calculate(container, 0.0005);
        handler.postProcessBoundaries(container);
        ASSERT_EQ(container.getSize(), 4);
        std::vector<std::array<double, 3>> expectedPositions{{15, 0.25,  0},
                                                             {5,  19.75, 0},
                                                             {0,  5,     0},
                                                             {0,  5,     0}};
        std::vector<Particle> particles = container.getParticles();
        for (int i = 0; i < 4; i++)
            ASSERT_ARRAYS_NEAR(particles[i].getX(), expectedPositions[i], 1e-6);
        // Second timestep - The two slower particles get deleted on the bottom and top
        handler.preProcessBoundaries(container);
        calculator->calculate(container, 0.0005);
        handler.postProcessBoundaries(container);
        ASSERT_EQ(container.getSize(), 4);
        particles.clear();
        particles = container.getParticles();
        expectedPositions = {{15, 0, 0},
                             {5, 0, 0},
                             {19.5, 5, 0},
                             {0.5, 5, 0}};
        for (int i = 0; i < 4; i++)
            ASSERT_ARRAYS_NEAR(particles[i].getX(), expectedPositions[i], 1e-6);
    }

    // Check if the forces after reflection are correct
    TEST(BoundaryHandlerTest, CornerPeriodic) {
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        std::array<double, 2> domain = {20.0, 20.0};
        std::unique_ptr<calculators::Calculator> calculator = std::make_unique<calculators::LJCalculator>(3.0);
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator.get(), 1.0};
        std::ofstream outfile("particles_near_reflecting_boundary.txt");
        outfile << "0\n"  // Data code for Particles
                << "4\n"  // Number of data sets
                << "2\n"  // Dimension of simulation
                << "0.5 0.5 0.0     -1000.0 -1000.0 0.0     1.0\n" // Bottom Left
                << "0.5 19.5 0.0    -1000.0 1000.0 0.0      1.0\n" // Top Left
                << "19.5 0.5 0.0     1000.0 -1000.0 0.0     1.0\n" // Bottom Right
                << "19.5 19.5 0.0    1000.0 1000.0 0.0      1.0\n";// Top Right
        outfile.close();

        // Read cuboid data from the file
        ParticleContainer container = fileReaders::TXTReader::readFile("particles_near_reflecting_boundary.txt");
        std::remove("particles_near_reflecting_boundary");

        // Check if Force of all Particles is zero
        std::array<double, 3> zero{0.0, 0.0, 0.0};
        for (Particle &p: container) {
            ASSERT_EQ(p.getF(), zero);
        }
        // First timestep - The faster two particles should be deleted on the left/right
        handler.preProcessBoundaries(container);
        calculator->calculate(container, 0.0005);
        handler.postProcessBoundaries(container);
        ASSERT_EQ(container.getSize(), 4);
        std::vector<Particle> particles = container.getParticles();
        for (int i = 0; i < 4; i++)
            ASSERT_ARRAYS_NEAR(particles[i].getX(), zero, 1e-6);
        // Second timestep - The two slower particles get deleted on the bottom and top
        handler.preProcessBoundaries(container);
        calculator->calculate(container, 0.0005);
        handler.postProcessBoundaries(container);
        ASSERT_EQ(container.getSize(), 4);
        particles.clear();
        particles = container.getParticles();
        std::vector<std::array<double, 3>> expectedPositions = {{19.5, 19.5, 0.0},
                                                                {19.5, 0.5, 0.0},
                                                                {0.5, 19.5, 0.0},
                                                                {0.5, 0.5, 0.0}};
        for (int i = 0; i < 4; i++)
            ASSERT_ARRAYS_NEAR(particles[i].getX(), expectedPositions[i], 1e-6);
    }
} //boundaries