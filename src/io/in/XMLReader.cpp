#include "XMLReader.h"
#include "input_schema.hxx"
#include "spdlog/spdlog.h"
#include <fstream>
#include <iostream>
#include <memory>

namespace fileReaders {

    SimulationDataContainer XMLReader::readFile(const std::string& filepath) {
        SPDLOG_INFO("Reading XML file: {}", filepath);

        std::unique_ptr<Simulation> simulation  = Simulation_(filepath);
        const auto& fileWriterParameters = simulation->FileWriterParameters();
        const auto& simulationParameters = simulation->SimulationParameters();
        const auto& thermostatParameters = simulation->ThermostatParameters();


        ParticleContainer particleContainer;
        loadCuboids(*simulation, particleContainer);

        SimulationDataContainer simulationDataContainer(particleContainer,
                                                        (FileWriterParameters &) fileWriterParameters,
                                                        (SimulationParameters &) simulationParameters,
                                                        (ThermostatParameters &) thermostatParameters);

        return simulationDataContainer;
    }

    void XMLReader::loadCuboids(const Simulation& simulation, ParticleContainer& particleContainer) {
        SPDLOG_INFO("Starting to load cuboids...");
        const auto& cuboids = simulation.Cuboids();

        for (const auto& cuboid : cuboids) {
            std::array<double, 3> llf{};
            std::array<size_t, 3> numParticles{};
            std::array<double, 3> startV{};
            double distance = cuboid.Distance();
            double mass = cuboid.Mass();
            double meanV = cuboid.MeanVelocity();

            std::istringstream coordStream(cuboid.Coordinates());
            std::istringstream partDimStream(cuboid.ParticlesPerDimension());
            std::istringstream initVelStream(cuboid.InitialVelocities());

            for (auto& value : llf) coordStream >> value;
            for (auto& value : numParticles) partDimStream >> value;
            for (auto& value : startV) initVelStream >> value;

            CuboidParameters cuboidParams(llf, numParticles, distance, mass, startV, meanV, 3);
            ParticleGenerator::generateCuboid(cuboidParams, particleContainer);
            particleContainer.initializePairs();
        }
        SPDLOG_INFO("Finished loading cuboids!");
    }

}  // namespace fileReaders
