//
// Created by kimj2 on 14.05.2024.
//
#include "calculators/SVCalculator.h"
#include "calculators/LJCalculator.h"
#include "calculators/LC_LJCalculator.h"
#include "io/in/FileReader.h"
#include "io/in/TXTReader.h"
#include "io/in/XMLReader.h"
#include "objects/ParticleContainer.h"
#include "objects/LinkedCellContainer.h"
#include "io/out/FileWriter.h"
#include "io/out/VTKWriter.h"
#include "io/out/XYZWriter.h"
#include "spdlog/spdlog.h"
#include "cxxopts.hpp"
#include "boundaries/BoundaryController.h"

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
     * This function processes the command line arguments using cxxopts. It sets up the
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
                                 double &delta_t, double &end_time, std::array<double, 3> &domain, double &cutoffRadius,
                                 ParticleContainer &particleContainer, LinkedCellContainer &linkedCellContainer,
                                 std::string &baseName, int &writerFrequency, std::vector<CuboidParameters> &cuboidParameters,
                                 std::unique_ptr<fileReaders::TXTReader> &TXTReader, std::unique_ptr<fileReaders::XMLReader> &XMLReader,
                                 std::unique_ptr<outputWriters::FileWriter> &outputWriter, std::unique_ptr<calculators::Calculator> &calculator,
                                 std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> &boundaryMap, int &simulationType) {
        cxxopts::Options options("MolSim", "Molecular Simulation Program");

        options.add_options()
                ("help", "Produce help message")
                ("input", "Input file path", cxxopts::value<std::string>())
                ("delta_t", "Set delta_t", cxxopts::value<double>()->default_value("0.014"))
                ("end_time", "Set end_time", cxxopts::value<double>()->default_value("1000"))
                ("output", "Output writer (vtk or xyz)", cxxopts::value<std::string>())
                ("calculator", "Calculator (sv, lj or dummy)", cxxopts::value<std::string>())
                ("boundaries", "Boundary conditions (0000 to 3333)", cxxopts::value<std::string>()->default_value("3333"));

        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return false;
        }

        if (result.count("input")) {
            inputFilePath = result["input"].as<std::string>();
            SPDLOG_INFO("Input file path: {}", inputFilePath);
            
            if (inputFilePath.length() >= 4 && inputFilePath.substr(inputFilePath.length() - 4) == ".xml") {
                SPDLOG_INFO("Detected XML file format.");

                XMLReader = std::make_unique<fileReaders::XMLReader>();
                XMLReader->readFileParameters(inputFilePath);
                double cellSize = 3.0;

                domain = XMLReader->getDomain();
                cutoffRadius = XMLReader->getCutoffRadius();
                baseName = XMLReader->getBaseName();
                writerFrequency = XMLReader->getWriterFrequency();
                delta_t = XMLReader->getDeltaT();
                end_time = XMLReader->getEndTime();
                cuboidParameters = XMLReader->getCuboidParameters();

                calculator = std::make_unique<calculators::LC_LJCalculator>();
                outputWriter = std::make_unique<outputWriters::VTKWriter>();

                linkedCellContainer = LinkedCellContainer(domain, cuboidParameters, cutoffRadius, cellSize);
                simulationType = 0;
                return true;
            }
            else {
                TXTReader = std::make_unique<fileReaders::TXTReader>();
                particleContainer = TXTReader->readFile(inputFilePath);
                simulationType = 1;
            }
        }

        delta_t = result["delta_t"].as<double>();
        end_time = result["end_time"].as<double>();

        if (result.count("output")) {
            std::string outputWriterArg = result["output"].as<std::string>();
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

        if (result.count("calculator")) {
            std::string calculatorArg = result["calculator"].as<std::string>();
            if (calculatorArg == "sv") {
                calculator = std::make_unique<calculators::SVCalculator>();
                SPDLOG_INFO("Selected calculator: sv");
            } else if (calculatorArg == "lj") {
                calculator = std::make_unique<calculators::LJCalculator>(5.31608);
                SPDLOG_INFO("Selected calculator: lj");
            } else {
                SPDLOG_ERROR("Invalid option for calculator: {}", calculatorArg);
                SPDLOG_ERROR("Only 'sv' and 'lj' are allowed.");
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
        if (result.count("boundaries")) {
            std::string boundariesArg = result["boundaries"].as<std::string>();
            if (boundariesArg.size() == 4) {
                std::array<boundaries::BoundaryDirection, 4> directions = {
                        boundaries::BoundaryDirection::LEFT,
                        boundaries::BoundaryDirection::BOTTOM,
                        boundaries::BoundaryDirection::RIGHT,
                        boundaries::BoundaryDirection::TOP
                };

                for (int i = 0; i < 4; ++i) {
                    switch (boundariesArg[i]) {
                        case '0':
                            boundaryMap[directions[i]] = boundaries::BoundaryType::OFF;
                            break;
                        case '1':
                            boundaryMap[directions[i]] = boundaries::BoundaryType::REFLECTING;
                            break;
                        case '2':
                            boundaryMap[directions[i]] = boundaries::BoundaryType::OUTFLOW;
                            break;
                        case '3':
                            boundaryMap[directions[i]] = boundaries::BoundaryType::PERIODIC;
                            break;
                        default:
                            SPDLOG_WARN("Invalid boundary value '{}', defaulting all to PERIODIC", boundariesArg[i]);
                            boundaryMap[directions[i]] = boundaries::BoundaryType::PERIODIC;
                    }
                }
            } else {
                SPDLOG_WARN("Invalid boundary string length, defaulting all boundaries to REFLECTING");
                boundaryMap[boundaries::BoundaryDirection::LEFT] = boundaries::BoundaryType::REFLECTING;
                boundaryMap[boundaries::BoundaryDirection::BOTTOM] = boundaries::BoundaryType::REFLECTING;
                boundaryMap[boundaries::BoundaryDirection::RIGHT] = boundaries::BoundaryType::REFLECTING;
                boundaryMap[boundaries::BoundaryDirection::TOP] = boundaries::BoundaryType::REFLECTING;
            }
        } else {
            SPDLOG_WARN("No boundary conditions specified, defaulting all boundaries to REFLECTING");
            boundaryMap[boundaries::BoundaryDirection::LEFT] = boundaries::BoundaryType::REFLECTING;
            boundaryMap[boundaries::BoundaryDirection::BOTTOM] = boundaries::BoundaryType::REFLECTING;
            boundaryMap[boundaries::BoundaryDirection::RIGHT] = boundaries::BoundaryType::REFLECTING;
            boundaryMap[boundaries::BoundaryDirection::TOP] = boundaries::BoundaryType::REFLECTING;
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
    * @param outputWriter The file writer to be used.
    * @param calculator The calculator to be used.
    */
    static void performSimulation(double &delta_t, double &end_time, std::array<double, 3> &domain, double &cutoffRadius, 
                                  ParticleContainer &particleContainer, LinkedCellContainer &linkedCellContainer,
                                  std::string &baseName, int &writerFrequency,std::vector<CuboidParameters> &cuboidParameters,
                                  std::unique_ptr<fileReaders::TXTReader> &TXTReader, std::unique_ptr<fileReaders::XMLReader> &XMLReader,
                                  std::unique_ptr<outputWriters::FileWriter> &outputWriter, std::unique_ptr<calculators::Calculator> &calculator,
                                  std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> &boundaryMap, int &simulationType) {
        if (simulationType == 0) {
            SPDLOG_INFO("Starting simulation with linked cells.");
            double current_time = 0.0; // start_time
            int iteration = 0;

            while (current_time < end_time) {
                SPDLOG_DEBUG("Starting iteration {}", iteration);
                calculator->calculateLC(linkedCellContainer, delta_t);

                iteration++;
                if (iteration % writerFrequency == 0) {
                    outputWriter->plotParticlesLC(iteration, linkedCellContainer, baseName);
                    SPDLOG_INFO("Printed output file at iteration {}", iteration);
                }

                if (iteration % 100 == 0) {
                    SPDLOG_INFO("Iteration {} finished.", iteration);
                }
                current_time += delta_t;
            }

        }
        else {
            const std::string &filename = "MD";

            double current_time = 0.0; // start_time
            int iteration = 0;

            std::array<double, 2> domain = {100.0, 100.0};

            const boundaries::BoundaryController controller{boundaryMap, calculator.get(), domain, 1.0};

            while (current_time < end_time) {

                controller.preProcessBoundaries(particleContainer);
                calculator->calculate(particleContainer, delta_t);
                controller.postProcessBoundaries(particleContainer);

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
    }
};
