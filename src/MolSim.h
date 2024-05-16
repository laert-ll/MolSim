//
// Created by kimj2 on 14.05.2024.
//
#pragma once

#include <iostream>
#include <memory>
#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>
#include "calculators/SVCalculator.h"
#include "calculators/DummyCalculator.h"
#include "calculators/LJCalculator.h"
#include "io/in/FileReader.h"
#include "objects/ParticleContainer.h"
#include "io/out/FileWriter.h"
#include "io/out/VTKWriter.h"
#include "io/out/XYZWriter.h"
#include "spdlog/spdlog.h"

class MolSim {
public:
    /**
     * @brief Sets the log level for the program.
     *
     * This function sets the log level for the program based on the input string.
     * The log level can be one of the following: TRACE, DEBUG, INFO, WARN, ERROR, CRITICAL, OFF.
     * If an invalid log level is provided, the function defaults to INFO.
     *
     * @param log_level The log level to set.
     */
    static void setLogLevel(const std::string &log_level) {
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
     * @brief Processes the command line arguments and sets up the simulation parameters.
     *
     * This function processes the command line arguments using Boost.Program_options. It sets up the
     * simulation parameters such as the time step (delta_t), the end time of the simulation, the output
     * writer, and the calculator to be used.
     *
     * The function accepts the following command line arguments:
     * - "--help": Prints the help message with all available options.
     * - "--delta_t": Sets the time step size for the simulation. Default is 0.014.
     * - "--end_time": Sets the end time for the simulation. Default is 1000.
     * - "--output": Specifies the output writer to be used. Options are 'vtk' or 'xyz'. Default is 'vtk'.
     * - "--calculator": Specifies the calculator to be used. Options are 'sv', 'lj', or 'dummy'.
     *
     * @param argc The number of command line arguments.
     * @param argv The array of command line arguments.
     * @param[out] delta_t The time step size for the simulation.
     * @param[out] end_time The end time for the simulation.
     * @param[out] outputWriter The output writer to be used.
     * @param[out] calculator The calculator to be used.
     *
     * @return True if the arguments were processed successfully and a valid calculator and output writer were selected, false otherwise.
     */
    static bool processArguments(int argc, char *argv[], std::string &inputFilePath,
                                    double &delta_t, double &end_time,
                                    std::unique_ptr<outputWriters::OutputWriter> &outputWriter,
                                    std::unique_ptr<calculators::Calculator> &calculator) {
        boost::program_options::options_description desc("Allowed options");
        desc.add_options()
                ("help", "produce help message")
                ("input", boost::program_options::value<std::string>(), "input file path")
                ("delta_t", boost::program_options::value<double>(&delta_t)->default_value(0.014), "set delta_t")
                ("end_time", boost::program_options::value<double>(&end_time)->default_value(1000), "set end_time")
                ("output", boost::program_options::value<std::string>(), "output writer (vtk or xyz)")
                ("calculator", boost::program_options::value<std::string>(), "calculator (sv or dummy)");

        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);

        if (vm.count("help")) {
            std::stringstream ss;
            desc.print(ss);
            SPDLOG_INFO("{}", ss.str());
            return false;
        }

        if (vm.count("input")) {
            inputFilePath = vm["input"].as<std::string>();
            SPDLOG_INFO("Input file path: {}", inputFilePath);
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

        if (inputFilePath.empty()) {
            SPDLOG_ERROR("Invalid input; please insert an input file.");
            return false;
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
    static void performSimulation(ParticleContainer &particleContainer, double &delta_t, double &end_time,
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
};

namespace po = boost::program_options;