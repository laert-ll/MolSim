#include "Calculator.h"
#include "FileReader.h"
#include "ParticleContainer.h"
#include "./test/CalculatorTest.h"

#include <iostream>

constexpr double start_time = 0;
constexpr double default_end_time = 1000;
constexpr double default_delta_t = 0.014;

bool parseArguments(int argc, char *argv[], double &delta_t, double &end_time, bool &testEnabled) {
    if (argc < 2 || argc > 5) {
        std::cerr << "Erroneous programme call! " << std::endl;
        std::cerr << "Usage: ./MolSym input_filename [delta_t] [end_time] [true]" << std::endl;
        return false;
    }

    char *endptr;
    if (argc >= 3) {
        delta_t = std::strtod(argv[2], &endptr);
        if (*endptr != '\0' || delta_t <= 0.0) {
            std::cerr << "Invalid number for delta_t: " << argv[2] << std::endl;
            return false;
        }
    }
    if (argc >= 4) {
        end_time = std::strtod(argv[3], &endptr);
        if (*endptr != '\0' || end_time <= 0.0) {
            std::cerr << "Invalid number for end_time: " << argv[3] << std::endl;
            return false;
        }
    }

    if (argc == 5) {
        std::string testArg = argv[4];
        std::transform(testArg.begin(), testArg.end(), testArg.begin(), ::tolower);
        if (testArg == "true") {
            testEnabled = true;
        } else if (testArg == "false") {
            testEnabled = false;
        } else {
            std::cerr << "Invalid option for testEnabled: " << argv[4] << std::endl;
            std::cerr << "Only 'true' or 'false' are allowed." << std::endl;
            return false;
        }
    }

    return true;
}

bool performSimulation(ParticleContainer &particleContainer, double &delta_t, double &end_time) {
    Calculator calculator;

    double current_time = start_time;
    int iteration = 0;

    while (current_time < end_time) {
        if (iteration > 1e6) {
            std::cerr << "Timeout. Number of iterations exceeded 1 Mio." << std::endl;
            return false;
        }
        calculator.calculate(particleContainer, delta_t);

        iteration++;
        if (iteration % 10 == 0) {
            calculator.plotParticles(iteration, particleContainer);
        }
        std::cout << "Iteration " << iteration << " finished." << std::endl;

        current_time += delta_t;
    }

    std::cout << "output written. Terminating..." << std::endl;
    return true;
}

int main(int argc, char *argsv[]) {
    // Example call: ./MolSim ./input/eingabe-sonne.txt 0.01 1 true

    std::cout << "Hello from MolSim for PSE!" << std::endl;

    FileReader fileReader;
    double delta_t = default_delta_t;
    double end_time = default_end_time;
    bool testEnabled = false;

    if (!parseArguments(argc, argsv, delta_t, end_time, testEnabled)) {
        return 1;
    }

    ParticleContainer particleContainer = fileReader.readFile(argsv[1]);

    std::cout << "Starting simulation with delta_t: " << delta_t << " and end_time: " << end_time << std::endl;
    bool success = performSimulation(particleContainer, delta_t, end_time);
    if (!success) {
        std::cout << "Error occurred during the simulation." << std::endl;
        return 1;
    }
    std::cout << "Simulation completed successfully" << std::endl;

    // Run Test
    if (testEnabled) {
        CalculatorTest calculatorTest(delta_t);
        calculatorTest.runTest();
    }

    return 0;
}
