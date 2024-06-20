//
// Created by U-jin Hong on 04.06.24.
//

#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

#include "boundaries/BoundaryHandler.h"
#include "calculators/LJCalculator.h"
#include "calculators/LC_LJCalculator.h"
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
        std::array<double, 3> domain = {20.0, 20.0, 10.0};
        boundaryMap.emplace(boundaries::BoundaryDirection::LEFT, boundaries::BoundaryType::REFLECTING);
        boundaryMap.emplace(boundaries::BoundaryDirection::RIGHT, boundaries::BoundaryType::REFLECTING);
        boundaryMap.emplace(boundaries::BoundaryDirection::TOP, boundaries::BoundaryType::REFLECTING);
        boundaryMap.emplace(boundaries::BoundaryDirection::BOTTOM, boundaries::BoundaryType::REFLECTING);
        std::shared_ptr<calculators::Calculator> calculator = std::make_shared<calculators::LJCalculator>(3.0);
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator};

        ParticleContainer container{};
        container.addParticle(Particle{std::array<double, 3>{10.0, 0.5, 0.0}, std::array<double, 3>{0.0, 3.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{10.0, 19.5, 0.0}, std::array<double, 3>{0.0, 3.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{0.5, 10., 0.0}, std::array<double, 3>{0.0, 3.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{19.5, 10., 0.0}, std::array<double, 3>{0.0, 3.0, 0.0}, 1.0, 0.0});

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
        std::array<double, 3> domain = {20.0, 20.0, 10.0};
        std::shared_ptr<calculators::Calculator> calculator = std::make_shared<calculators::LJCalculator>(3.0);
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        boundaryMap[BoundaryDirection::TOP] = boundaries::BoundaryType::REFLECTING;
        boundaryMap[BoundaryDirection::BOTTOM] = boundaries::BoundaryType::REFLECTING;
        boundaryMap[BoundaryDirection::LEFT] = boundaries::BoundaryType::REFLECTING;
        boundaryMap[BoundaryDirection::RIGHT] = boundaries::BoundaryType::REFLECTING;
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator};

        ParticleContainer container{};
        container.addParticle(Particle{std::array<double, 3>{0.5, 0.5, 0.0}, std::array<double, 3>{-3.0, -3.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{0.5, 19.5, 0.0}, std::array<double, 3>{-3.0, -3.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{19.5, 0.5, 0.0}, std::array<double, 3>{3.0, -3.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{19.5, 19.5, 0.0}, std::array<double, 3>{3.0, -3.0, 0.0}, 1.0, 0.0});

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

        std::array<double, 3> domain = {20.0, 20.0, 10.0};
        std::shared_ptr<calculators::Calculator> calculator = std::make_shared<calculators::LJCalculator>(3.0);
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator};

        ParticleContainer container{};
        container.addParticle(Particle{std::array<double, 3>{10.0, 0.5, 0.0}, std::array<double, 3>{0.0, -500.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{10.0, 19.5, 0.0}, std::array<double, 3>{0.0, 500.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{0.5, 10.0, 0.0}, std::array<double, 3>{-1000.0, 0.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{19.5, 10.0, 0.0}, std::array<double, 3>{2000.0, 0.0, 0.0}, 1.0, 0.0});

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
        boundaryMap[BoundaryDirection::TOP] = boundaries::BoundaryType::REFLECTING;
        boundaryMap[BoundaryDirection::LEFT] = boundaries::BoundaryType::REFLECTING;
        std::array<double, 3> domain = {20.0, 20.0, 10.0};
        std::shared_ptr<calculators::Calculator> calculator = std::make_shared<calculators::LJCalculator>(3.0);
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator};

        ParticleContainer container{};
        container.addParticle(Particle{std::array<double, 3>{10.0, 0.5, 0.0}, std::array<double, 3>{0.0, -300.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{10.0, 19.5, 0.0}, std::array<double, 3>{0.0, -300.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{0.5, 10.0, 0.0}, std::array<double, 3>{-300.0, 0.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{19.5, 10.0, 0.0}, std::array<double, 3>{1000.0, 0.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{0.5, 0.5, 0.0}, std::array<double, 3>{-300.0, -300.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{0.5, 19.5, 0.0}, std::array<double, 3>{-300.0, 300.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{19.5, 0.5, 0.0}, std::array<double, 3>{1000.0, -300.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{19.5, 19.5, 0.0}, std::array<double, 3>{1000.0, 300.0, 0.0}, 1.0, 0.0});

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
                                                             {10.0, 19.35, 0.0},
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
        expectedForces = {{0, 1.2851430767584855, 0},
                          {20000.0, 0.0,      0.0},
                          {20000.0, -20000.0, 0.0}};
        expectedPositions = {{10, 18.899958292097978, 0},
                             {-0.09245500000000006, 10.0,               0.0},
                             {-0.09245500000000006, 20.092454999999998, 0.0}};
        for (int i = 0; i < 3; i++) {
            ASSERT_ARRAYS_NEAR(particles[i].getOldF(), expectedForces[i], 1e-6);
            ASSERT_ARRAYS_NEAR(particles[i].getX(), expectedPositions[i], 1e-6);
        }
    }

    TEST(BoundaryHandlerTest, PeriodicBoundaries) {
        std::array<double, 3> domain = {20.0, 20.0, 10.0};
        std::shared_ptr<calculators::Calculator> calculator = std::make_shared<calculators::LJCalculator>(3.0);
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        boundaryMap[BoundaryDirection::TOP] = boundaries::BoundaryType::PERIODIC;
        boundaryMap[BoundaryDirection::BOTTOM] = boundaries::BoundaryType::PERIODIC;
        boundaryMap[BoundaryDirection::LEFT] = boundaries::BoundaryType::PERIODIC;
        boundaryMap[BoundaryDirection::RIGHT] = boundaries::BoundaryType::PERIODIC;
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator};
        ParticleContainer container{};
        container.addParticle(Particle{std::array<double, 3>{15.0, 0.5, 0.0}, std::array<double, 3>{0.0, -500.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{5.0, 19.5, 0.0}, std::array<double, 3>{0.0, 500.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{0.5, 5.0, 0.0}, std::array<double, 3>{-1000.0, 0.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{19.5, 15.0, 0.0}, std::array<double, 3>{1000.0, 0.0, 0.0}, 1.0, 0.0});

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
                                                             {0,  15.0,     0}};
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
                             {0.5, 15, 0}};
        for (int i = 0; i < 4; i++)
            ASSERT_ARRAYS_NEAR(particles[i].getX(), expectedPositions[i], 1e-6);
    }

    // Check if the forces after reflection are correct
    TEST(BoundaryHandlerTest, CornerPeriodic) {
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        boundaryMap[BoundaryDirection::TOP] = boundaries::BoundaryType::PERIODIC;
        boundaryMap[BoundaryDirection::BOTTOM] = boundaries::BoundaryType::PERIODIC;
        boundaryMap[BoundaryDirection::LEFT] = boundaries::BoundaryType::PERIODIC;
        boundaryMap[BoundaryDirection::RIGHT] = boundaries::BoundaryType::PERIODIC;
        std::array<double, 3> domain = {20.0, 20.0, 10.0};
        std::shared_ptr<calculators::Calculator> calculator = std::make_shared<calculators::LJCalculator>(3.0);
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator};

        // Read cuboid data from the file
        ParticleContainer container{};
        container.addParticle(Particle{std::array<double, 3>{0.5, 0.5, 0.0}, std::array<double, 3>{-1000.0, -1000.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{0.5, 19.5, 0.0}, std::array<double, 3>{-1000.0, 1000.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{19.5, 0.5, 0.0}, std::array<double, 3>{1000.0, -1000.0, 0.0}, 1.0, 0.0});
        container.addParticle(Particle{std::array<double, 3>{19.5, 19.5, 0.0}, std::array<double, 3>{1000.0, 1000.0, 0.0}, 1.0, 0.0});
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

    TEST(BoundaryHandlerTest, BasicReflectionLC) {
        SPDLOG_INFO("Testing Reflections...");
        SPDLOG_INFO("Setting up boundary map and domain...");
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        std::array<double, 3> domain = {20.0, 20.0, 10.0};
        SPDLOG_INFO("Emplacing boundary directions and types...");
        boundaryMap.emplace(boundaries::BoundaryDirection::LEFT, boundaries::BoundaryType::REFLECTING);
        boundaryMap.emplace(boundaries::BoundaryDirection::RIGHT, boundaries::BoundaryType::REFLECTING);
        boundaryMap.emplace(boundaries::BoundaryDirection::TOP, boundaries::BoundaryType::REFLECTING);
        boundaryMap.emplace(boundaries::BoundaryDirection::BOTTOM, boundaries::BoundaryType::REFLECTING);
        SPDLOG_INFO("Creating calculator shared pointer...");
        std::shared_ptr<calculators::Calculator> calculator = std::make_shared<calculators::LC_LJCalculator>();
        SPDLOG_INFO("Setting up boundary properties...");
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        SPDLOG_INFO("Initializing BoundaryHandler...");
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator};
        SPDLOG_INFO("BoundaryHandler initialized successfully.");

        LinkedCellContainer container{};
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{10.0, 0.5, 0.0}, std::array<double, 3>{0.0, 3.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{10.0, 19.5, 0.0}, std::array<double, 3>{0.0, 3.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{0.5, 10., 0.0}, std::array<double, 3>{0.0, 3.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{19.5, 10., 0.0}, std::array<double, 3>{0.0, 3.0, 0.0}, 1.0, 0.0}));

        // Check if Force of all Particles is zero
        SPDLOG_INFO("Checking if force of all particles is zero...");
        std::array<double, 3> zero{0.0, 0.0, 0.0};
        for (const auto &p: container)  {
            ASSERT_EQ(p->getF(), zero);
        }
        std::vector<std::array<double, 3>> expectedReflectedForces{{0.0,    120.0,  0.0},
                                                                   {0.0,    -120.0, 0.0},
                                                                   {120.0,  0.0,    0.0},
                                                                   {-120.0, 0.0,    0.0}};
        SPDLOG_INFO("Processing boundaries...");
        handler.preProcessBoundaries(container);
        SPDLOG_INFO("Getting particles from container...");
        std::vector<std::shared_ptr<Particle>> particles = container.getParticles();
        for (int i = 0; i < 4; i++) {
            ASSERT_ARRAYS_NEAR(particles[i].get()->getF(), expectedReflectedForces[i], 1e-6);
            SPDLOG_INFO("Particle {} added with coordinates ({},{},{}) and force ({},{},{})",
                        i,
                        particles[i]->getX()[0], particles[i]->getX()[1], particles[i]->getX()[2],
                        particles[i]->getF()[0], particles[i]->getF()[1], particles[i]->getF()[2]);
        }
    }


// Testing Particles moving against every reflecting boundary
// Check if the forces after reflection are correct
    TEST(BoundaryHandlerTest, CornerReflectionLC) {
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        std::array<double, 3> domain = {20.0, 20.0, 10.0};
        std::shared_ptr<calculators::Calculator> calculator = std::make_shared<calculators::LC_LJCalculator>();
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        boundaryMap[BoundaryDirection::TOP] = boundaries::BoundaryType::REFLECTING;
        boundaryMap[BoundaryDirection::BOTTOM] = boundaries::BoundaryType::REFLECTING;
        boundaryMap[BoundaryDirection::LEFT] = boundaries::BoundaryType::REFLECTING;
        boundaryMap[BoundaryDirection::RIGHT] = boundaries::BoundaryType::REFLECTING;
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator};

        LinkedCellContainer container{};
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{0.5, 0.5, 0.0}, std::array<double, 3>{-3.0, -3.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{0.5, 19.5, 0.0}, std::array<double, 3>{-3.0, -3.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{19.5, 0.5, 0.0}, std::array<double, 3>{3.0, -3.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{19.5, 19.5, 0.0}, std::array<double, 3>{3.0, -3.0, 0.0}, 1.0, 0.0}));

        // Check if Force of all Particles is zero
        std::array<double, 3> zero{0.0, 0.0, 0.0};
        for (const auto &p: container)  {
            ASSERT_EQ(p->getF(), zero);
        }
        std::vector<std::array<double, 3>> expectedReflectedForces{{120.0,  120.0,  0},
                                                                   {120.0,  -120.0, 0},
                                                                   {-120.0, 120.0,  0},
                                                                   {-120.0, -120.0, 0}};
        handler.preProcessBoundaries(container);
        std::vector<std::shared_ptr<Particle>> particles = container.getParticles();
        for (int i = 0; i < 4; i++) {
            ASSERT_ARRAYS_NEAR(particles[i].get()->getF(), expectedReflectedForces[i], 1e-6);
        }
    }


    TEST(BoundaryHandlerTest, BasicOutflowLC) {
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        boundaryMap.emplace(boundaries::BoundaryDirection::LEFT, boundaries::BoundaryType::OUTFLOW);
        boundaryMap.emplace(boundaries::BoundaryDirection::RIGHT, boundaries::BoundaryType::OUTFLOW);
        boundaryMap.emplace(boundaries::BoundaryDirection::BOTTOM, boundaries::BoundaryType::OUTFLOW);
        boundaryMap.emplace(boundaries::BoundaryDirection::TOP, boundaries::BoundaryType::OUTFLOW);

        std::array<double, 3> domain = {20.0, 20.0, 10.0};
        std::shared_ptr<calculators::Calculator> calculator = std::make_shared<calculators::LC_LJCalculator>();
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator};

        LinkedCellContainer container{};
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{10.0, 0.5, 0.0}, std::array<double, 3>{0.0, -500.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{10.0, 19.5, 0.0}, std::array<double, 3>{0.0, 500.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{0.5, 10.0, 0.0}, std::array<double, 3>{-1000.0, 0.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{19.5, 10.0, 0.0}, std::array<double, 3>{2000.0, 0.0, 0.0}, 1.0, 0.0}));

        // Check if Force of all Particles is zero
        std::array<double, 3> zero{0.0, 0.0, 0.0};
        for (const auto &p: container)  {
            ASSERT_EQ(p->getF(), zero);
        }
        // First timestep - The faster two particles should be deleted on the left/right
        handler.preProcessBoundaries(container);
        calculator->calculateLC(container, 0.0005);
        handler.postProcessBoundaries(container);
        ASSERT_EQ(container.getSize(), 2);
        // Second timestep - The two slower particles get deleted on the bottom and top
        handler.preProcessBoundaries(container);
        calculator->calculateLC(container, 0.0005);
        handler.postProcessBoundaries(container);
        ASSERT_EQ(container.getSize(), 0);
    }

    // Check the Behaviour of two reflecting boundaries top and left, two outflow boundaries bottom and right
    TEST(BoundaryHandlerTest, MixedBoundariesLC) {
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        boundaryMap.emplace(boundaries::BoundaryDirection::BOTTOM, boundaries::BoundaryType::OUTFLOW);
        boundaryMap.emplace(boundaries::BoundaryDirection::RIGHT, boundaries::BoundaryType::OUTFLOW);
        boundaryMap[BoundaryDirection::TOP] = boundaries::BoundaryType::REFLECTING;
        boundaryMap[BoundaryDirection::LEFT] = boundaries::BoundaryType::REFLECTING;
        std::array<double, 3> domain = {20.0, 20.0, 10.0};
        std::shared_ptr<calculators::Calculator> calculator = std::make_shared<calculators::LC_LJCalculator>();
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator};

        LinkedCellContainer container{};
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{10.0, 0.5, 0.0}, std::array<double, 3>{0.0, -300.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{10.0, 19.5, 0.0}, std::array<double, 3>{0.0, -300.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{0.5, 10.0, 0.0}, std::array<double, 3>{-300.0, 0.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{19.5, 10.0, 0.0}, std::array<double, 3>{1000.0, 0.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{0.5, 0.5, 0.0}, std::array<double, 3>{-300.0, -300.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{0.5, 19.5, 0.0}, std::array<double, 3>{-300.0, 300.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{19.5, 0.5, 0.0}, std::array<double, 3>{1000.0, -300.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{19.5, 19.5, 0.0}, std::array<double, 3>{1000.0, 300.0, 0.0}, 1.0, 0.0}));

        // Check if Force of all Particles is zero
        std::array<double, 3> zero{0.0, 0.0, 0.0};
        for (const auto &p: container)  {
            ASSERT_EQ(p->getF(), zero);
        }
        handler.preProcessBoundaries(container);
        calculator->calculateLC(container, 0.0005);
        handler.postProcessBoundaries(container);
        std::vector<std::shared_ptr<Particle>> particles = container.getParticles();
        ASSERT_EQ(container.getSize(), 5);
        //First iteration
        std::vector<std::array<double, 3>> expectedForces{{0.0,   0.0,    0.0},
                                                          {0.0,   -120.0, 0.0},
                                                          {120.0, 0.0,    0.0},
                                                          {120.0, 0.0,    0.0},
                                                          {120.0, -120.0, 0.0}};
        std::vector<std::array<double, 3>> expectedPositions{{10.0, 0.35,  0.0},
                                                             {10.0, 19.35, 0.0},
                                                             {0.35, 10.0,  0.0},
                                                             {0.35, 0.35,  0.0},
                                                             {0.35, 19.65, 0.0}};
        for (int i = 0; i < 5; i++) {
            ASSERT_ARRAYS_NEAR(particles[i].get()->getOldF(), expectedForces[i], 1e-6);
            ASSERT_ARRAYS_NEAR(particles[i].get()->getX(), expectedPositions[i], 1e-6);
        }
        for (int i = 0; i < 3; i++) {
            handler.preProcessBoundaries(container);
            calculator->calculateLC(container, 0.0005);
            handler.postProcessBoundaries(container);
        }
        expectedForces.clear();
        expectedPositions.clear();
        particles.clear();
        particles = container.getParticles();
        ASSERT_EQ(container.getSize(), 3);
        expectedForces = {{0, 1.2851430767584855, 0},
                          {20000.0, 0.0,      0.0},
                          {20000.0, -20000.0, 0.0}};
        expectedPositions = {{10, 18.899958292097978, 0},
                             {-0.09245500000000006, 10.0,               0.0},
                             {-0.09245500000000006, 20.092454999999998, 0.0}};
        for (int i = 0; i < 3; i++) {
            ASSERT_ARRAYS_NEAR(particles[i].get()->getOldF(), expectedForces[i], 1e-6);
            ASSERT_ARRAYS_NEAR(particles[i].get()->getX(), expectedPositions[i], 1e-6);
        }
    }

    TEST(BoundaryHandlerTest, PeriodicBoundariesLC) {
        std::array<double, 3> domain = {20.0, 20.0, 10.0};
        std::shared_ptr<calculators::Calculator> calculator = std::make_shared<calculators::LC_LJCalculator>();
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        boundaryMap[BoundaryDirection::TOP] = boundaries::BoundaryType::PERIODIC;
        boundaryMap[BoundaryDirection::BOTTOM] = boundaries::BoundaryType::PERIODIC;
        boundaryMap[BoundaryDirection::LEFT] = boundaries::BoundaryType::PERIODIC;
        boundaryMap[BoundaryDirection::RIGHT] = boundaries::BoundaryType::PERIODIC;
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator};
        LinkedCellContainer container{};
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{15.0, 0.5, 0.0}, std::array<double, 3>{0.0, -500.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{5.0, 19.5, 0.0}, std::array<double, 3>{0.0, 500.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{0.5, 5.0, 0.0}, std::array<double, 3>{-1000.0, 0.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{19.5, 15.0, 0.0}, std::array<double, 3>{1000.0, 0.0, 0.0}, 1.0, 0.0}));

        // Check if Force of all Particles is zero
        std::array<double, 3> zero{0.0, 0.0, 0.0};
        for (const auto &p: container)  {
            ASSERT_EQ(p->getF(), zero);
        }
        // First timestep - The faster two particles should be deleted on the left/right
        handler.preProcessBoundaries(container);
        calculator->calculateLC(container, 0.0005);
        handler.postProcessBoundaries(container);
        ASSERT_EQ(container.getSize(), 4);
        std::vector<std::array<double, 3>> expectedPositions{{15, 0.25,  0},
                                                             {5,  19.75, 0},
                                                             {0,  5,     0},
                                                             {0,  15.0,     0}};
        std::vector<std::shared_ptr<Particle>> particles = container.getParticles();
        for (int i = 0; i < 4; i++)
            ASSERT_ARRAYS_NEAR(particles[i].get()->getX(), expectedPositions[i], 1e-6);
        // Second timestep - The two slower particles get deleted on the bottom and top
        handler.preProcessBoundaries(container);
        calculator->calculateLC(container, 0.0005);
        handler.postProcessBoundaries(container);
        ASSERT_EQ(container.getSize(), 4);
        particles.clear();
        particles = container.getParticles();
        expectedPositions = {{15, 0, 0},
                             {5, 0, 0},
                             {19.5, 5, 0},
                             {0.5, 15, 0}};
        for (int i = 0; i < 4; i++)
            ASSERT_ARRAYS_NEAR(particles[i]->getX(), expectedPositions[i], 1e-6);
    }

    // Check if the forces after reflection are correct
    TEST(BoundaryHandlerTest, CornerPeriodicLC) {
        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap{};
        boundaryMap[BoundaryDirection::TOP] = boundaries::BoundaryType::PERIODIC;
        boundaryMap[BoundaryDirection::BOTTOM] = boundaries::BoundaryType::PERIODIC;
        boundaryMap[BoundaryDirection::LEFT] = boundaries::BoundaryType::PERIODIC;
        boundaryMap[BoundaryDirection::RIGHT] = boundaries::BoundaryType::PERIODIC;
        std::array<double, 3> domain = {20.0, 20.0, 10.0};
        std::shared_ptr<calculators::Calculator> calculator = std::make_shared<calculators::LC_LJCalculator>();
        boundaries::BoundaryProperties properties{domain, boundaryMap};
        // Initialization of BoundaryHandler
        boundaries::BoundaryHandler handler{properties, calculator};

        // Read cuboid data from the file
        LinkedCellContainer container{};
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{0.5, 0.5, 0.0}, std::array<double, 3>{-1000.0, -1000.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{0.5, 19.5, 0.0}, std::array<double, 3>{-1000.0, 1000.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{19.5, 0.5, 0.0}, std::array<double, 3>{1000.0, -1000.0, 0.0}, 1.0, 0.0}));
        container.addParticle(std::make_shared<Particle>(Particle{std::array<double, 3>{19.5, 19.5, 0.0}, std::array<double, 3>{1000.0, 1000.0, 0.0}, 1.0, 0.0}));

        // Check if Force of all Particles is zero
        std::array<double, 3> zero{0.0, 0.0, 0.0};
        for (const auto &p: container)  {
            ASSERT_EQ(p->getF(), zero);
        }
        // First timestep - The faster two particles should be deleted on the left/right
        handler.preProcessBoundaries(container);
        calculator->calculateLC(container, 0.0005);
        handler.postProcessBoundaries(container);
        ASSERT_EQ(container.getSize(), 4);
        std::vector<std::shared_ptr<Particle>> particles = container.getParticles();
        for (int i = 0; i < 4; i++)
            ASSERT_ARRAYS_NEAR(particles[i].get()->getX(), zero, 1e-6);
        // Second timestep - The two slower particles get deleted on the bottom and top
        handler.preProcessBoundaries(container);
        calculator->calculateLC(container, 0.0005);
        handler.postProcessBoundaries(container);
        ASSERT_EQ(container.getSize(), 4);
        particles.clear();
        particles = container.getParticles();
        std::vector<std::array<double, 3>> expectedPositions = {{19.5, 19.5, 0.0},
                                                                {19.5, 0.5, 0.0},
                                                                {0.5, 19.5, 0.0},
                                                                {0.5, 0.5, 0.0}};
        for (int i = 0; i < 4; i++)
            ASSERT_ARRAYS_NEAR(particles[i].get()->getX(), expectedPositions[i], 1e-6);
    }
}//boundaries