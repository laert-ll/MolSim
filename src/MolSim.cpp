#include "calculators/SVCalculator.h"
#include "calculators/DummyCalculator.h"
#include "calculators/LJCalculator.h"
#include "io/in/FileReader.h"
#include "objects/ParticleContainer.h"
#include "io/out/FileWriter.h"
#include "io/out/VTKWriter.h"
#include "io/out/XYZWriter.h"

#include <iostream>
#include <memory>

/**
 * @brief Processes the command line arguments and sets the corresponding variables.
 *
 * This function processes the command line arguments and sets the delta_t, end_time,
 * outputWriter, and calculator variables based on the provided arguments.
 *
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 * @param delta_t Reference to the delta_t variable to be set.
 * @param end_time Reference to the end_time variable to be set.
 * @param outputWriter Reference to the outputWriter unique pointer to be set.
 * @param calculator Reference to the calculator unique pointer to be set.
 *
 * @return True if the arguments were processed successfully, false otherwise.
 */
bool processArguments(int argc, char *argv[], double &delta_t, double &end_time,
                      std::unique_ptr<outputWriters::OutputWriter> &outputWriter,
                      std::unique_ptr<calculators::Calculator> &calculator) {
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
        std::string outputWriterArg = argv[4];
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

    if (argc == 6) {
        std::string calculatorArg = argv[5];
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

/**
 * @brief Performs the simulation.
 *
 * This function performs the simulation by calling the calculate method of the calculator for each
 * time step and writing the particle positions to the output file at regular intervals.
 *
 * @param particleContainer The particle container containing the particles.
 * @param delta_t The time step size.
 * @param end_time The end time of the simulation.
 * @param outputWriter The output writer to be used.
 * @param calculator The calculator to be used.
 */
void performSimulation(ParticleContainer &particleContainer, double &delta_t, double &end_time,
                       std::unique_ptr<outputWriters::OutputWriter> &outputWriter,
                       std::unique_ptr<calculators::Calculator> &calculator) {
    const std::string &filename = "MD";

    double current_time = 0; // start_time
    int iteration = 0;

    while (current_time < end_time) {
        calculator->calculate(particleContainer, delta_t);

        iteration++;
        if (iteration % 10 == 0) {
            outputWriter->plotParticles(iteration, particleContainer, filename);
        }

        if (iteration % 100 == 0) {
            std::cout << "Iteration " << iteration << " finished." << std::endl;
        }

        current_time += delta_t;
    }

    std::cout << "output written. Terminating..." << std::endl;
}

/**
 * @brief The main function of the program.
 *
 * This function is the entry point of the program. It reads the command line arguments, processes
 * them, reads the input file and performs the simulation.
 *
 * @param argc The number of command line arguments.
 * @param argsv The array of command line arguments.
 *
 * @return The exit status of the program.
 */
int main(int argc, char *argsv[]) {
    // Example call: ./MolSim ./resources/input-sun.txt 0.01 1 true vtk sv
    // Example call 2: ./MolSim ./resources/input-cuboid.txt

    std::cout << "Hello from MolSim for PSE!" << std::endl;

    double delta_t = 0.0002; // default-delte_t
    double end_time = 5; // default_end_time
    std::unique_ptr<outputWriters::OutputWriter> outputWriter = std::make_unique<outputWriters::VTKWriter>();;
//    std::unique_ptr<calculators::Calculator> calculator;
    std::unique_ptr<calculators::Calculator> calculator = std::make_unique<calculators::LJCalculator>(1, 5);
//    ParticleContainer particleContainer = fileReader.loadParticles(argsv[1]);
    ParticleContainer particleContainer = FileReader::loadCuboid(argsv[1]);

//    if (!processArguments(argc, argsv, delta_t, end_time, outputWriter, calculator)) {
//        return 1;
//    }

    std::cout << "Starting simulation with delta_t: " << delta_t << " and end_time: " << end_time << std::endl;
    performSimulation(particleContainer, delta_t, end_time, outputWriter, calculator);
    std::cout << "Simulation completed." << std::endl;

    return 0;
}