#include "XMLReader.h"
#include "input_schema.hxx"
#include "spdlog/spdlog.h"
#include <fstream>
#include <iostream>
#include <memory>

namespace fileReaders {

    SimulationDataContainer XMLReader::readFile(const std::string &filepath) {
        SPDLOG_INFO("Reading XML file: {}", filepath);

        std::unique_ptr<Simulation> simulation = Simulation_(filepath);

        std::unique_ptr<ParticleContainer> particleContainer = std::make_unique<ParticleContainer>();
        loadCuboids(*simulation, *particleContainer);

        std::unique_ptr<FileWriterParameters> fileWriterParameters = std::make_unique<FileWriterParameters>(loadFileWriterParameters(*simulation));
        std::unique_ptr<SimulationParameters> simulationParameters = std::make_unique<SimulationParameters>(loadSimulationParameters(*simulation));
        std::unique_ptr<ThermostatParameters> thermostatParameters = std::make_unique<ThermostatParameters>(loadThermostatParameters(*simulation));

        SimulationDataContainer simulationDataContainer(std::move(particleContainer),
                                                        std::move(fileWriterParameters),
                                                        std::move(simulationParameters),
                                                        std::move(thermostatParameters));

        return simulationDataContainer;
    }

    FileWriterParameters XMLReader::loadFileWriterParameters(const Simulation &simulation) {
        const auto &fileWriterParametersParsed = simulation.FileWriterParameters();
        return {fileWriterParametersParsed.BaseName(), fileWriterParametersParsed.WriteFrequency()};
    }

    SimulationParameters XMLReader::loadSimulationParameters(const Simulation &simulation) {
        const auto &simulationParametersParsed = simulation.SimulationParameters();
        return {simulationParametersParsed.EndT(), simulationParametersParsed.DeltaT()};
    }

    ThermostatParameters XMLReader::loadThermostatParameters(const Simulation &simulation) {
        const auto &thermostatParametersParsed = simulation.ThermostatParameters();
        return {thermostatParametersParsed.StartTemperature(), thermostatParametersParsed.TargetTemperature(),
                thermostatParametersParsed.ApplyFrequency(), thermostatParametersParsed.MaxDeltaTemperature(),
                thermostatParametersParsed.Dimension()};
    }

    void XMLReader::loadCuboids(const Simulation &simulation, ParticleContainer &particleContainer) {
        SPDLOG_INFO("Starting to load cuboids...");
        const auto &cuboids = simulation.Cuboids();

        for (const auto &cuboid: cuboids) {
            std::array<double, 3> llf{};
            std::array<size_t, 3> numParticles{};
            std::array<double, 3> startV{};
            double distance = cuboid.Distance();
            double mass = cuboid.Mass();
            double meanV = cuboid.MeanVelocity();

            std::istringstream coordStream(cuboid.Coordinates());
            std::istringstream partDimStream(cuboid.ParticlesPerDimension());
            std::istringstream initVelStream(cuboid.InitialVelocities());

            for (auto &value: llf) coordStream >> value;
            for (auto &value: numParticles) partDimStream >> value;
            for (auto &value: startV) initVelStream >> value;

            CuboidParameters cuboidParams(llf, numParticles, distance, mass, startV, meanV, 3);
            ParticleGenerator::generateCuboid(cuboidParams, particleContainer);
            particleContainer.initializePairs();
        }
        SPDLOG_INFO("Finished loading cuboids!");
    }

}  // namespace fileReaders
