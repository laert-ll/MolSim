#include "calculators/SVCalculator.h"
#include "calculators/LJCalculator.h"
#include "calculators/LCCalculator.h"
#include "io/in/FileReader.h"
#include "objects/ParticleContainer.h"
#include "io/out/FileWriter.h"
#include "io/out/VTKWriter.h"
#include "io/out/XYZWriter.h"
#include "cxxopts.hpp"
#include "spdlog/spdlog.h"
#include "MolSim.h"
#include <iostream>
#include <memory>
#include <map>
#include "boundaries/BoundaryController.h"

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
    // Example calls:
    // ./MolSim --help
    // ./MolSim ../resources/input-sun.txt --delta_t=0.001 --end_time=5 --output=vtk --calculator=sv
    // ./MolSim ../resources/input-cuboid.txt --delta_t=0.001 --end_time=5 --output=vtk --calculator=lj

    // Set the log level to the wanted level
    std::string log_level = LOG_LEVEL;
    MolSim::setLogLevel(log_level);

    std::string inputFilePath;
    double delta_t;
    double end_time;
    std::unique_ptr<outputWriters::FileWriter> outputWriter;
    std::unique_ptr<calculators::Calculator> calculator;
    std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap;

    if (!MolSim::processArguments(argc, argsv, inputFilePath, delta_t, end_time, outputWriter, calculator, boundaryMap)) {
        return 1;
    }

    ParticleContainer particleContainer = FileReader::readFile(inputFilePath);

    SPDLOG_INFO("Starting simulation with delta_t: {}, end_time: {}", delta_t, end_time);

    MolSim::performSimulation(particleContainer, delta_t, end_time, outputWriter, calculator, boundaryMap);

    SPDLOG_INFO("Simulation completed.");

    return 0;
}