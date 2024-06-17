#include "io/in/FileReader.h"
#include "io/in/TXTReader.h"
#include "io/in/XMLReader.h"
#include "objects/ParticleContainer.h"
#include "objects/LinkedCellContainer.h"
#include "io/out/FileWriter.h"
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
    // Set the log level to the wanted level
    std::string log_level = LOG_LEVEL;
    MolSim::setLogLevel(log_level);

    std::string inputFilePath;
    double delta_t;
    double end_time;
    std::array<double, 3> domain;
    double cutoffRadius;
    std::string baseName;
    int writerFrequency;
    std::vector<CuboidParameters> cuboidParameters;
    ParticleContainer particleContainer;
    LinkedCellContainer linkedCellContainer;
    std::unique_ptr<fileReaders::TXTReader> TXTReader;
    std::unique_ptr<fileReaders::XMLReader> XMLReader;
    std::unique_ptr<outputWriters::FileWriter> outputWriter;
    std::unique_ptr<calculators::Calculator> calculator;
    std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap;
    int simulationType;

    if (!MolSim::processArguments(argc, argsv, inputFilePath, delta_t, end_time, domain, cutoffRadius, particleContainer, linkedCellContainer,
                                    baseName, writerFrequency, cuboidParameters, TXTReader, XMLReader, outputWriter, calculator, boundaryMap, simulationType)) {
        return 1;
    }

    SPDLOG_INFO("Starting simulation");

    MolSim::performSimulation(delta_t, end_time, domain, cutoffRadius, particleContainer, linkedCellContainer, baseName, writerFrequency, 
                            cuboidParameters, TXTReader, XMLReader, outputWriter, calculator, boundaryMap, simulationType);

    SPDLOG_INFO("Simulation completed.");

    return 0;
}


// fix arguments of process arguments
// fix arguments of perform simulation
