#include "XMLReader.h"
#include "input_schema.hxx"
#include "spdlog/spdlog.h"
#include "objects/LinkedCellContainer.h"
#include <fstream>
#include <iostream>
#include <memory>

namespace fileReaders {

    SimulationDataContainer XMLReader::readFile(const std::string &filepath) {
        SPDLOG_INFO("Reading XML file: {}", filepath);

        std::unique_ptr<Simulation> simulation = Simulation_(filepath);


        std::unique_ptr<FileWriterParameters> fileWriterParameters = std::make_unique<FileWriterParameters>(loadFileWriterParameters(*simulation));
        std::unique_ptr<SimulationParameters> simulationParameters = std::make_unique<SimulationParameters>(loadSimulationParameters(*simulation));
        std::unique_ptr<ThermostatParameters> thermostatParameters = std::make_unique<ThermostatParameters>(loadThermostatParameters(*simulation));
        std::unique_ptr<LinkedCellsParameters> linkedCellParameters = std::make_unique<LinkedCellsParameters>(loadLinkedCellsParameters(*simulation));
        std::unique_ptr<BoundaryParameters> boundaryParameters = std::make_unique<BoundaryParameters>(loadBoundaryParameters(*simulation));

        std::unique_ptr<ParticleContainer> particleContainer = std::make_unique<ParticleContainer>();
        std::unique_ptr<LinkedCellContainer> linkedCellContainer = std::make_unique<LinkedCellContainer>();
        if (linkedCellParameters->isLinkedCellsUsed()) {
            const double cutoffRadius = linkedCellParameters->getCutOffRadius();
            linkedCellContainer->setCellSize(cutoffRadius);
            linkedCellContainer->setCutOffRadius(cutoffRadius);
            linkedCellContainer->setDomain(boundaryParameters->getDomain());
            loadCuboids(*simulation, *linkedCellContainer);
        } else {
            loadCuboids(*simulation, *particleContainer);
        }

        SimulationDataContainer simulationDataContainer(std::move(particleContainer),
                                                        std::move(linkedCellContainer),
                                                        std::move(fileWriterParameters),
                                                        std::move(simulationParameters),
                                                        std::move(thermostatParameters),
                                                        std::move(linkedCellParameters),
                                                        std::move(boundaryParameters));

        return simulationDataContainer;
    }

    LinkedCellsParameters XMLReader::loadLinkedCellsParameters(const Simulation &simulation) {
        const auto &linkedCellParametersParsed = simulation.LinkedCellsParameters();
        return {linkedCellParametersParsed.LinkedCellsUsed(), linkedCellParametersParsed.CutoffRadius()};
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

    BoundaryParameters XMLReader::loadBoundaryParameters(const Simulation &simulation) {
        const auto &boundaryParametersParsed = simulation.BoundaryParameters();

        std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap;

        boundaryMap[boundaries::BoundaryDirection::TOP] = stringToBoundaryType(boundaryParametersParsed.TOP());
        boundaryMap[boundaries::BoundaryDirection::RIGHT] = stringToBoundaryType(boundaryParametersParsed.RIGHT());
        boundaryMap[boundaries::BoundaryDirection::BOTTOM] = stringToBoundaryType(boundaryParametersParsed.BOTTOM());
        boundaryMap[boundaries::BoundaryDirection::LEFT] = stringToBoundaryType(boundaryParametersParsed.LEFT());
        boundaryMap[boundaries::BoundaryDirection::FRONT] = stringToBoundaryType(boundaryParametersParsed.FRONT());
        boundaryMap[boundaries::BoundaryDirection::BACK] = stringToBoundaryType(boundaryParametersParsed.BACK());

        std::array<double, 3> domain{};
        std::istringstream domainStream(boundaryParametersParsed.Domain());
        for (auto &value: domain) domainStream >> value;

        return {boundaryMap, domain};
    }

    boundaries::BoundaryType XMLReader::stringToBoundaryType(const std::string& boundaryTypeStr) {
        if (boundaryTypeStr == "REFLECTING") {
            return boundaries::BoundaryType::REFLECTING;
        } else if (boundaryTypeStr == "OUTFLOW") {
            return boundaries::BoundaryType::OUTFLOW;
        } else if (boundaryTypeStr == "PERIODIC") {
            return boundaries::BoundaryType::PERIODIC;
        } else if (boundaryTypeStr == "OFF") {
            return boundaries::BoundaryType::OFF;
        } else {
            throw std::invalid_argument("Invalid boundary type string: " + boundaryTypeStr);
        }
    }

    void XMLReader::loadCuboids(const Simulation &simulation, ParticleContainer &particleContainer) {
        SPDLOG_INFO("Starting to load cuboids into a particle container...");
        const auto &cuboids = simulation.Cuboid();

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
        }
        particleContainer.initializePairs();
        SPDLOG_INFO("Finished loading cuboids into a particle container!");
    }

    void XMLReader::loadCuboids(const Simulation &simulation, LinkedCellContainer &linkedCellContainer) {
        SPDLOG_INFO("Starting to load cuboids into a linked-cell container...");
        const auto &cuboids = simulation.Cuboid();

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
            ParticleGenerator::generateCuboid(cuboidParams, linkedCellContainer);
        }
        linkedCellContainer.initializeAndPopulateCells();
        SPDLOG_INFO("Finished loading cuboids into a linked-cell container!");
    }

}  // namespace fileReaders
