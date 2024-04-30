#include "Calculator.h"
#include "FileReader.h"
#include "ParticleContainer.h"
#include "./test/CalculatorTest.h"
#include "outputWriters/OutputWriter.h"
#include "outputWriters/VTKWriter.h"
#include "outputWriters/XYZWriter.h"

#include <iostream>
#include <memory>

constexpr double start_time = 0;
constexpr double default_end_time = 1000;
constexpr double default_delta_t = 0.014;

bool processArguments(int argc, char *argv[], double &delta_t, double &end_time, bool &testEnabled,
                      std::unique_ptr<outputWriters::OutputWriter> &outputWriter) {
    if (argc < 2 || argc > 6) {
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

    if (argc >= 5) {
        std::string testEnabledArg = argv[4];
        std::transform(testEnabledArg.begin(), testEnabledArg.end(), testEnabledArg.begin(), ::tolower);
        if (testEnabledArg == "true") {
            testEnabled = true;
        } else if (testEnabledArg == "false") {
            testEnabled = false;
        } else {
            std::cerr << "Invalid option for testEnabled: " << argv[4] << std::endl;
            std::cerr << "Only 'true' or 'false' are allowed." << std::endl;
            return false;
        }
    }

    if (argc == 6) {
        std::string outputWriterArg = argv[5];
        std::transform(outputWriterArg.begin(), outputWriterArg.end(), outputWriterArg.begin(), ::tolower);
        if (outputWriterArg == "vtk") {
            outputWriter = std::make_unique<outputWriters::VTKWriter>();
        } else if (outputWriterArg == "xyz") {
            outputWriter = std::make_unique<outputWriters::XYZWriter>();
        } else {
            std::cerr << "Invalid option for output writer: " << argv[4] << std::endl;
            std::cerr << "Only 'vtk' or 'xyz' are allowed." << std::endl;
            return false;
        }
    } else {
        // Default to VTKWriter if no argument is provided
        outputWriter = std::make_unique<outputWriters::VTKWriter>();
    }

    return true;
}

bool performSimulation(ParticleContainer &particleContainer, double &delta_t, double &end_time,
                       std::unique_ptr<outputWriters::OutputWriter> &outputWriter) {
    Calculator calculator;
    const std::string &filename = "MD";

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
            outputWriter->plotParticles(iteration, particleContainer, filename);
        }
        std::cout << "Iteration " << iteration << " finished." << std::endl;

        current_time += delta_t;
    }

    std::cout << "output written. Terminating..." << std::endl;
    return true;
}

int main(int argc, char *argsv[]) {
    // Example call: ./MolSim ./input/eingabe-sonne.txt 0.01 1 true vtk

    std::cout << "Hello from MolSim for PSE!" << std::endl;

    FileReader fileReader;
    double delta_t = default_delta_t;
    double end_time = default_end_time;
    bool testEnabled = false;
    std::unique_ptr<outputWriters::OutputWriter> outputWriter;

    if (!processArguments(argc, argsv, delta_t, end_time, testEnabled, outputWriter)) {
        return 1;
    }

    ParticleContainer particleContainer = fileReader.readFile(argsv[1]);

    std::cout << "Starting simulation with delta_t: " << delta_t << " and end_time: " << end_time << std::endl;
    bool success = performSimulation(particleContainer, delta_t, end_time, outputWriter);
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
