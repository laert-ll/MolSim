//
// Created by kimj2 on 05.06.2024.
//
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include "XMLReader.h"
#include "ParticleGenerator.h"
#include "resources/SimulationInputSpec.hxx"
#include "spdlog/spdlog.h"

namespace fileReaders {
    SimulationDataContainer XMLReader::readFile(const std::string &filename) {
        // Parse the XML file
        std::unique_ptr<SimulationInput> simInput;
        try {
            simInput = SimulationInput_(filename, xml_schema::flags::dont_validate);
        } catch (const xsd::cxx::tree::parsing<char> &e) {
            // Handle parsing errors
            SPDLOG_ERROR("Error parsing XML file: {}", filename);
            throw std::runtime_error("Error parsing XML file: {}" + filename);
        }

        ParticleContainer particleContainer;

        // Iterate over the cuboids in the XML and generate particles for each one
        for (const auto &cuboid: simInput->Cuboids().Cuboid()) {
            CuboidParameters params(
                    {cuboid.LowerLeftFrontCorner().X(), cuboid.LowerLeftFrontCorner().Y(),
                     cuboid.LowerLeftFrontCorner().Z()},
                    {static_cast<unsigned long>(cuboid.NumParticlesPerDimension().X()),
                     static_cast<unsigned long>(cuboid.NumParticlesPerDimension().Y()),
                     static_cast<unsigned long>(cuboid.NumParticlesPerDimension().Z())},
                    cuboid.Distance(),
                    cuboid.Mass(),
                    {cuboid.StartV().X(), cuboid.StartV().Y(), cuboid.StartV().Z()},
                    cuboid.MeanV(),
                    cuboid.Dimension()
            );
            ParticleGenerator::generateCuboid(params, particleContainer);
        }

        FileWriterParameters fileWriterParameters(simInput->OutputFiles().BaseName(),
                                                  simInput->OutputFiles().WriteFrequency());
        SimulationParameters simulationParameters(simInput->SimulationParameters().EndT(),
                                                  simInput->SimulationParameters().DeltaT());
        SimulationDataContainer simulationDataContainer = SimulationDataContainer(particleContainer,
                                                                                  fileWriterParameters,
                                                                                  simulationParameters);
        return simulationDataContainer;
    }
}// namespace fileReaders

