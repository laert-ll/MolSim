 //
 // Created by kimj2 on 26.04.2024.
 //

 #ifndef CALCULATORTEST_H
 #define CALCULATORTEST_H

 #include "../Particle.h"
 #include "../Calculator.h"
 #include <iostream>
 #include <vector>
 #include <cmath>
 #include <list>

/**
 * @class CalculatorTest
 * @brief A class for testing the Calculator class.
 *
 * This class is used to test the functionality of the Calculator class.
 * It initializes a set of particles, runs a simulation, and checks the resulting positions.
 */
 class CalculatorTest {
 private:
     /**
      * @brief The container for particles used in the test.
      */
     ParticleContainer particleContainer;

     /**
     * @brief The time step used in the simulation.
     */
     double timeStep;

     /**
     * @brief The calculator object used for the simulation.
     */
     Calculator calculator;

 public:

     /**
     * @brief Constructor for CalculatorTest.
     * @param delta_t The time step for the simulation.
     *
     * Initializes the particle container, time step, and calculator with the provided time step.
     */
     explicit CalculatorTest(double delta_t) : particleContainer(ParticleContainer()), timeStep(delta_t), calculator(Calculator()) {}

     /**
     * @brief Initializes the particles for the test.
     *
     * This function should initialize the particles in the particle container with the test values.
     */
     void initializeParticlesForTest();

     /**
     * @brief Runs the simulation.
     * @param endTime The end time of the simulation.
     * @param delta_t The time step for the simulation.
     *
     * This function should run the simulation for the specified end time and time step.
     */
     void runSimulation(double endTime, double delta_t);

     /**
      * @brief Checks the positions of the particles.
      * @return True if the positions are as expected, false otherwise.
      *
      * This function should check the positions of the particles after the simulation and compare them to the expected values.
      */
     bool checkPositions();

     /**
     * @brief Runs the test.
     *
     * This function should initialize the particles, run the simulation, and check the positions.
     * It should output the results of the test.
     */
     void runTest();
 };

 #endif