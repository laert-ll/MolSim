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
        std::stringstream ss;
        desc.print(ss);
        SPDLOG_INFO("{}", ss.str());
        return false;
    }

    if (vm.count("output")) {
        std::string outputWriterArg = vm["output"].as<std::string>();
        if (outputWriterArg == "vtk") {
            outputWriter = std::make_unique<outputWriters::VTKWriter>();
            SPDLOG_INFO("Selected output writer: vtk");
        } else if (outputWriterArg == "xyz") {
            outputWriter = std::make_unique<outputWriters::XYZWriter>();
            SPDLOG_INFO("Selected output writer: xyz");
        } else {
            SPDLOG_ERROR("Invalid option for output writer: {}", outputWriterArg);
            SPDLOG_ERROR("Only 'vtk' or 'xyz' are allowed.");
            return false;
        }
    }

    if (vm.count("calculator")) {
        std::string calculatorArg = vm["calculator"].as<std::string>();
        if (calculatorArg == "sv") {
            calculator = std::make_unique<calculators::SVCalculator>();
            SPDLOG_INFO("Selected calculator: sv");
        } else if (calculatorArg == "lj") {
            calculator = std::make_unique<calculators::LJCalculator>(1, 5);
            SPDLOG_INFO("Selected calculator: lj");
        } else if (calculatorArg == "dummy") {
            calculator = std::make_unique<calculators::DummyCalculator>();
            SPDLOG_INFO("Selected calculator: dummy");
        } else {
            SPDLOG_ERROR("Invalid option for calculator: {}", calculatorArg);
            SPDLOG_ERROR("Only 'sv' and 'dummy' are allowed.");
            return false;
        }
    }

    if (!outputWriter) {
        outputWriter = std::make_unique<outputWriters::VTKWriter>();
        SPDLOG_INFO("Selected output writer: vtk (default)");
    }

    if (!calculator) {
        SPDLOG_ERROR("Invalid input; please select a calculator.");
        return false;
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
            SPDLOG_INFO("Iteration {} finished.", iteration);
        }

        current_time += delta_t;
    }

    SPDLOG_INFO("Output written. Terminating...");
}

void setLogLevel(const std::string &log_level) {
    if (log_level == "TRACE") {
        spdlog::set_level(spdlog::level::trace);
    } else if (log_level == "DEBUG") {
        spdlog::set_level(spdlog::level::debug);
    } else if (log_level == "INFO") {
        spdlog::set_level(spdlog::level::info);
    } else if (log_level == "WARN") {
        spdlog::set_level(spdlog::level::warn);
    } else if (log_level == "ERROR") {
        spdlog::set_level(spdlog::level::err);
    } else if (log_level == "CRITICAL") {
        spdlog::set_level(spdlog::level::critical);
    } else if (log_level == "OFF") {
        spdlog::set_level(spdlog::level::off);
    } else {
        SPDLOG_WARN("Invalid log level: {}. Defaulting to INFO.", log_level);
        spdlog::set_level(spdlog::level::info);
    }
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
    std::string log_level = LOG_LEVEL;
    setLogLevel(log_level);


    double delta_t;
    double end_time;
    std::unique_ptr<outputWriters::OutputWriter> outputWriter;
    std::unique_ptr<calculators::Calculator> calculator;

    if (!processArguments(argc, argsv, delta_t, end_time, outputWriter, calculator)) {
        return 1;
    }

    ParticleContainer particleContainer = FileReader::readFile(argsv[1]);

    SPDLOG_INFO("Starting simulation with delta_t: {}, end_time: {}", delta_t, end_time);
    boost::timer::cpu_timer timer;

    performSimulation(particleContainer, delta_t, end_time, outputWriter, calculator);

    timer.stop();
    SPDLOG_INFO("Simulation completed.");
    SPDLOG_INFO("Elapsed time: {}", timer.format(2, "%w seconds"));

    return 0;
}
