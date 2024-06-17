//
// Created by kimj2 on 15.06.2024.
//
#include <gtest/gtest.h>
#include <sstream>
#include "../../../src/io/in/XMLReader.h"

const double COMPARISON_TOLERANCE = 1e-6;

TEST(XMLReaderTest, ReadFileTest) {
    const auto fileReader = std::make_unique<fileReaders::XMLReader>();
    SimulationDataContainer data = fileReader->readFile("./tests/io/in/XMLReaderTest.xml");

    EXPECT_EQ(data.getFileWriterParameters()->getBaseName(), "test");
    EXPECT_EQ(data.getFileWriterParameters()->getWriteFrequency(), 10);
    EXPECT_NEAR(data.getSimulationParameters()->getEnd_t(), 100.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getSimulationParameters()->getDelta_t(), 0.1, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getThermostatParameters()->getStartTemp(), 300.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getThermostatParameters()->getTargetTemp(), 300.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getThermostatParameters()->getMaxDeltaTemp(), 10.0, COMPARISON_TOLERANCE);
    EXPECT_EQ(data.getThermostatParameters()->getDimension(), 3);

    auto boundaryMap = data.getBoundaryParameters()->getBoundaryMap();
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::TOP], boundaries::BoundaryType::REFLECTING);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::RIGHT], boundaries::BoundaryType::OUTFLOW);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::BOTTOM], boundaries::BoundaryType::REFLECTING);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::LEFT], boundaries::BoundaryType::PERIODIC);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::FRONT], boundaries::BoundaryType::OFF);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::BACK], boundaries::BoundaryType::OFF);

    EXPECT_EQ(data.getParticleContainer()->getSize(), 125);
}