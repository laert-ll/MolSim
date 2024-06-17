#include "XMLReader.h"
#include "input_schema.hxx"
#include "spdlog/spdlog.h"
#include <fstream>
#include <iostream>
#include <memory>

namespace fileReaders {

    void XMLReader::readFileParameters(const std::string& filepath) {
        SPDLOG_INFO("Reading XML file: {}", filepath);

        std::unique_ptr<Simulation> simulation = Simulation_(filepath);

        const auto& inputParams = simulation->InputParameters();

        // Extract the required parameters from the simulation configuration
        domain = {inputParams.Domain().x(), inputParams.Domain().y(), inputParams.Domain().z()};
        cutoffRadius = inputParams.CutoffRadius();
        delta_t = inputParams.DeltaT();
        end_time = inputParams.EndTime();
        baseName = inputParams.BaseName();
        writerFrequency = inputParams.WriteFrequency();

        // Populate cuboidParameters from the simulation configuration
        const auto& cuboids = simulation->Cuboid();

        for (const auto& cuboid : cuboids) {
            std::array<double, 3> llf;
            std::array<size_t, 3> numParticles;
            std::array<double, 3> startV;
            double distance = cuboid.Distance();
            double mass = cuboid.Mass();
            double meanV = cuboid.MeanVelocity();

            std::istringstream coordStream(cuboid.Coordinates());
            std::istringstream partDimStream(cuboid.ParticlesPerDimension());
            std::istringstream initVelStream(cuboid.InitialVelocities());

            for (auto& value : llf) coordStream >> value;
            for (auto& value : numParticles) partDimStream >> value;
            for (auto& value : startV) initVelStream >> value;

            CuboidParameters cuboidParams(llf, numParticles, distance, mass, startV, meanV);
            cuboidParameters.push_back(cuboidParams);
        }
    }

    std::array<double, 3> XMLReader::getDomain() const {
        return domain;
    }

    double XMLReader::getCutoffRadius() const {
        return cutoffRadius;
    }

    double XMLReader::getDeltaT() const {
        return delta_t;
    }

    double XMLReader::getEndTime() const {
        return end_time;
    }

    std::string XMLReader::getBaseName() const {
        return baseName;
    }

    int XMLReader::getWriterFrequency() const {
        return writerFrequency;
    }

    std::vector<CuboidParameters> XMLReader::getCuboidParameters() const {
        return cuboidParameters;
    }

}  // namespace fileReaders
