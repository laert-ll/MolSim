#include "calculators/SVCalculator.h"
#include "calculators/DummyCalculator.h"
#include "calculators/LJCalculator.h"
#include "io/in/FileReader.h"
#include "objects/ParticleContainer.h"
#include "io/out/FileWriter.h"
#include "io/out/VTKWriter.h"
#include "io/out/XYZWriter.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <memory>
#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>

namespace po = boost::program_options;

bool processArguments(int argc, char *argv[], double &delta_t, double &end_time,
                      std::unique_ptr<outputWriters::OutputWriter> &outputWriter,
                      std::unique_ptr<calculators::Calculator> &calculator) {
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("delta_t", po::value<double>(&delta_t)->default_value(0.014), "set delta_t")
        ("end_time", po::value<double>(&end_time)->default_value(1000), "set end_time")
        ("output", po::value<std::string>(), "output writer (vtk or xyz)")
        ("calculator", po::value<std::string>(), "calculator (sv or dummy)");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        exit(0);
    }

    if (vm.count("output")) {
        std::string outputWriterArg = vm["output"].as<std::string>();
        if (outputWriterArg == "vtk") {
            outputWriter = std::make_unique<outputWriters::VTKWriter>();
            std::cout << "Selected output writer: vtk" << std::endl;
        } else if (outputWriterArg == "xyz") {
            outputWriter = std::make_unique<outputWriters::XYZWriter>();
            std::cout << "Selected output writer: xyz" << std::endl;
        } else {
            std::cerr << "Invalid option for output writer: " << outputWriterArg << std::endl;
            std::cerr << "Only 'vtk' or 'xyz' are allowed." << std::endl;
            exit(0);
        }
    }

    if (vm.count("calculator")) {
        std::string calculatorArg = vm["calculator"].as<std::string>();
        if (calculatorArg == "sv") {
            calculator = std::make_unique<calculators::SVCalculator>();
            std::cout << "Selected calculator: sv" << std::endl;
        } else if (calculatorArg == "lj") {
            calculator = std::make_unique<calculators::LJCalculator>(1, 5);
            std::cout << "Selected calculator: lj" << std::endl;
        } else if (calculatorArg == "dummy") {
            calculator = std::make_unique<calculators::DummyCalculator>();
            std::cout << "Selected calculator: dummy" << std::endl;
        } else {
            std::cerr << "Invalid option for calculator: " << calculatorArg << std::endl;
            std::cerr << "Only 'sv' and 'dummy' are allowed." << std::endl;
            exit(0);
        }
    }

    if (!outputWriter) {
        outputWriter = std::make_unique<outputWriters::VTKWriter>();
        std::cout << "Selected output writer: vtk (default)" << std::endl;
    }

    if (!calculator) {
        std::cout << "Invalid input; please select a calculator." << std::endl;
        exit(0);
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
            spdlog::info("Iteration {} finished.", iteration);
        }

        current_time += delta_t;
    }

    spdlog::info("Output written. Terminating...");
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
    // Example calls:
    // ./MolSim --help
    // ./MolSim ../resources/input-sun.txt --delta_t=0.001 --end_time=5 --output=vtk --calculator=sv
    // ./MolSim ../resources/input-cuboid.txt --delta_t=0.001 --end_time=5 --output=vtk --calculator=lj

    // Set the log level to the wanted level
    spdlog::set_level(spdlog::level::debug); // TODO: make it changable using command line argument (boost)

    double delta_t;
    double end_time;
    std::unique_ptr<outputWriters::OutputWriter> outputWriter;
    std::unique_ptr<calculators::Calculator> calculator;
    processArguments(argc, argsv, delta_t, end_time, outputWriter, calculator);

    ParticleContainer particleContainer = FileReader::readFile(argsv[1]);

    SPDLOG_INFO("Starting simulation with delta_t: {}, end_time: {}", delta_t, end_time);
    boost::timer::cpu_timer timer;

    performSimulation(particleContainer, delta_t, end_time, outputWriter, calculator);

    timer.stop();
    SPDLOG_INFO("Simulation completed.");
    SPDLOG_INFO("Elapsed time: {}", timer.format(2, "%w seconds"));

    return 0;
}
