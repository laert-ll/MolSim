#include "calculators/SVCalculator.h"
#include "calculators/DummyCalculator.h"
#include "io/in/FileReader.h"
#include "objects/ParticleContainer.h"
#include "test/CalculatorTest.h"
#include "outputWriters/OutputWriter.h"
#include "outputWriters/VTKWriter.h"
#include "outputWriters/XYZWriter.h"

#include <iostream>
#include <memory>

constexpr double start_time = 0;
constexpr double default_end_time = 1000;
constexpr double default_delta_t = 0.014;

bool processArguments(int argc, char *argv[], double &delta_t, double &end_time, bool &testEnabled,
                      std::unique_ptr<outputWriters::OutputWriter> &outputWriter,
                      std::unique_ptr<calculators::Calculator> &calculator) {
    if (argc < 2 || argc > 7) {
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

    if (argc >= 6) {
        std::string outputWriterArg = argv[5];
        std::transform(outputWriterArg.begin(), outputWriterArg.end(), outputWriterArg.begin(), ::tolower);
        if (outputWriterArg == "vtk") {
            outputWriter = std::make_unique<outputWriters::VTKWriter>();
            std::cout << "Selected output writer: vtk" << std::endl;
        } else if (outputWriterArg == "xyz") {
            outputWriter = std::make_unique<outputWriters::XYZWriter>();
            std::cout << "Selected output writer: xyz" << std::endl;
        } else {
            std::cerr << "Invalid option for output writer: " << argv[4] << std::endl;
            std::cerr << "Only 'vtk' or 'xyz' are allowed." << std::endl;
            return false;
        }
    }

    if (argc == 7) {
        std::string calculatorArg = argv[6];
        std::transform(calculatorArg.begin(), calculatorArg.end(), calculatorArg.begin(), ::tolower);
        if (calculatorArg == "sv") {
            calculator = std::make_unique<calculators::SVCalculator>();
            std::cout << "Selected calculator: sv" << std::endl;
        } else if (calculatorArg == "dummy") {
            calculator = std::make_unique<calculators::DummyCalculator>();
            std::cout << "Selected calculator: dummy" << std::endl;
        } else {
            std::cerr << "Invalid option for calculator: " << argv[5] << std::endl;
            std::cerr << "Only 'sv' and 'dummy' are allowed." << std::endl;
            return false;
        }
    }

    if (!outputWriter) {
        outputWriter = std::make_unique<outputWriters::VTKWriter>();
        std::cout << "Selected output writer: vtk (default)" << std::endl;
    }

    if (!calculator) {
        calculator = std::make_unique<calculators::SVCalculator>();
        std::cout << "Selected calculator: sv (default)" << std::endl;
    }

    return true;
}

bool performSimulation(ParticleContainer &particleContainer, double &delta_t, double &end_time,
                       std::unique_ptr<outputWriters::OutputWriter> &outputWriter,
                       std::unique_ptr<calculators::Calculator> &calculator) {
    const std::string &filename = "MD";

    double current_time = start_time;
    int iteration = 0;

    while (current_time < end_time) {
        if (iteration > 1e6) {
            std::cerr << "Timeout. Number of iterations exceeded 1 Mio." << std::endl;
            return false;
        }
        calculator->calculate(particleContainer, delta_t);

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
    // Example call: ./MolSim ../input/eingabe-sonne.txt 0.01 1 true vtk sv

    std::cout << "Hello from MolSim for PSE!" << std::endl;

    FileReader fileReader;
    double delta_t = default_delta_t;
    double end_time = default_end_time;
    bool testEnabled = false;
    std::unique_ptr<outputWriters::OutputWriter> outputWriter;
    std::unique_ptr<calculators::Calculator> calculator;
    ParticleContainer particleContainer = fileReader.readParticleData(argsv[1]);

    if (!processArguments(argc, argsv, delta_t, end_time, testEnabled, outputWriter, calculator)) {
        return 1;
    }

    std::cout << "Starting simulation with delta_t: " << delta_t << " and end_time: " << end_time << std::endl;
    bool success = performSimulation(particleContainer, delta_t, end_time, outputWriter, calculator);
    if (!success) {
        std::cout << "Error occurred during the simulation." << std::endl;
        return 1;
    }
    std::cout << "Simulation completed successfully" << std::endl;

    // Run Test
    if (testEnabled) {
        CalculatorTest calculatorTest(delta_t);
        calculatorTest.setCalculator(std::move(calculator));
        calculatorTest.runTest();
    }

    return 0;
}
