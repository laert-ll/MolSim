#include "calculators/SVCalculator.h"
#include "calculators/LJCalculator.h"
#include "io/in/FileReader.h"
#include "io/in/TXTReader.h"
#include "io/in/XMLReader.h"
#include "objects/ParticleContainer.h"
#include "objects/LinkedCellContainer.h"
#include "io/out/FileWriter.h"
#include "io/out/VTKWriter.h"
#include "io/out/XYZWriter.h"
#include "cxxopts.hpp"
#include "spdlog/spdlog.h"
#include "MolSim.h"
#include <iostream>
#include <memory>
#include <map>
#include "boundaries/BoundaryHandler.h"
#include "calculators/Thermostat.h"

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
    // Set the log level to the wanted level
    std::string log_level = LOG_LEVEL;
    MolSim::setLogLevel(log_level);
    std::string inputFilePath;
    double delta_t = -1.0;
    double end_time = -1.0;
    std::unique_ptr<fileReaders::FileReader> fileReader;
    std::unique_ptr<outputWriters::FileWriter> outputWriter;
    std::shared_ptr<calculators::Calculator> calculator;
    // std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap;
    std::unique_ptr<Thermostat> thermostat = std::make_unique<Thermostat>(10, 20, 5, 1, 3);

    if (!MolSim::processArguments(argc, argsv, inputFilePath, delta_t, end_time, outputWriter, calculator)) {
        return 1;
    }

    if (inputFilePath.length() >= 4 && inputFilePath.substr(inputFilePath.length() - 4) == ".xml") {
        SPDLOG_INFO("Processing XML input file: {}", inputFilePath);
        fileReader = std::make_unique<fileReaders::XMLReader>();
    } else {
        SPDLOG_INFO("Processing TXT input file: {}", inputFilePath);
        fileReader = std::make_unique<fileReaders::TXTReader>();
    }

    SimulationDataContainer simulationDataContainer = fileReader->readFile(inputFilePath);
    MolSim::updateSimulationParameters(simulationDataContainer, delta_t, end_time);
    MolSim::performSimulation(simulationDataContainer, outputWriter, calculator);

    SPDLOG_INFO("Simulation completed.");

    return 0;
}