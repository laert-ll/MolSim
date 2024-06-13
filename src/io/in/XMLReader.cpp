#include "FileReader.h"
#include "XMLReader.h"
#include "input_schema.hxx"
#include "spdlog/spdlog.h"

namespace fileReaders {

    ParticleContainer XMLReader::readFile(const std::string& filepath) {
        SPDLOG_INFO("Reading XML file: {}", filepath);

        ParticleContainer container;

        std::unique_ptr<Simulation> simulation = Simulation_(filepath);

        InputParametersType inputParams = simulation->InputParameters();
        SPDLOG_INFO("Input Parameters:");
        SPDLOG_INFO("  BaseName: {}", inputParams.BaseName());
        SPDLOG_INFO("  WriteFrequency: {}", inputParams.WriteFrequency());
        SPDLOG_INFO("  DeltaT: {}", inputParams.DeltaT());
        SPDLOG_INFO("  EndTime: {}", inputParams.EndTime());

        return container;
    }
}
