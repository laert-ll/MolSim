//
// Created by kimj2 on 15.06.2024.
//
#include <gtest/gtest.h>
#include <sstream>
#include "../../../src/io/in/XMLReader.h"

const double COMPARISON_TOLERANCE = 1e-6;

TEST(XMLReaderTest, ReadCuboidFileTest) {
    const auto fileReader = std::make_unique<fileReaders::XMLReader>();
    SimulationDataContainer data = fileReader->readFile("./tests/io/in/XMLReaderTestCuboid.xml");

    EXPECT_EQ(data.getFileWriterParameters()->getBaseName(), "testCuboid");
    EXPECT_EQ(data.getFileWriterParameters()->getWriteFrequency(), 10);

    EXPECT_NEAR(data.getSimulationParameters()->getEnd_t(), 100.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getSimulationParameters()->getDelta_t(), 0.1, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getSimulationParameters()->getGravity(), 0.0, COMPARISON_TOLERANCE);
    EXPECT_EQ(data.getSimulationParameters()->getDimension(), 2);

    EXPECT_NEAR(data.getThermostatParameters()->getStartTemp(), 300.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getThermostatParameters()->getTargetTemp(), 300.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getThermostatParameters()->getMaxDeltaTemp(), 10.0, COMPARISON_TOLERANCE);
    EXPECT_EQ(data.getThermostatParameters()->getDimension(), 3);

    EXPECT_EQ(data.getLinkedCellsParameters()->isLinkedCellsUsed(), false);
    EXPECT_NEAR(data.getLinkedCellsParameters()->getCutOffRadius(), 3.0, COMPARISON_TOLERANCE);

    auto boundaryMap = data.getBoundaryParameters()->getBoundaryMap();
    EXPECT_NEAR(data.getBoundaryParameters()->getDomain()[0], 180.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getBoundaryParameters()->getDomain()[1], 90.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getBoundaryParameters()->getDomain()[2], 3.0, COMPARISON_TOLERANCE);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::TOP], boundaries::BoundaryType::REFLECTING);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::RIGHT], boundaries::BoundaryType::OUTFLOW);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::BOTTOM], boundaries::BoundaryType::REFLECTING);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::LEFT], boundaries::BoundaryType::PERIODIC);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::FRONT], boundaries::BoundaryType::OFF);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::BACK], boundaries::BoundaryType::OFF);

    EXPECT_EQ(data.getParticleContainer()->getSize(), 125);
    EXPECT_EQ(data.getLinkedCellContainer()->getSize(), 0);
}

TEST(XMLReaderTest, ReadCuboidFileLCTest) {
    const auto fileReader = std::make_unique<fileReaders::XMLReader>();
    SimulationDataContainer data = fileReader->readFile("./tests/io/in/XMLReaderTestLCCuboid.xml");

    EXPECT_EQ(data.getFileWriterParameters()->getBaseName(), "testCuboid");
    EXPECT_EQ(data.getFileWriterParameters()->getWriteFrequency(), 10);

    EXPECT_NEAR(data.getSimulationParameters()->getEnd_t(), 100.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getSimulationParameters()->getDelta_t(), 0.1, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getSimulationParameters()->getGravity(), -9.81, COMPARISON_TOLERANCE);
    EXPECT_EQ(data.getSimulationParameters()->getDimension(), 2);

    EXPECT_NEAR(data.getThermostatParameters()->getStartTemp(), 300.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getThermostatParameters()->getTargetTemp(), 300.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getThermostatParameters()->getMaxDeltaTemp(), 10.0, COMPARISON_TOLERANCE);
    EXPECT_EQ(data.getThermostatParameters()->getDimension(), 3);

    EXPECT_EQ(data.getLinkedCellsParameters()->isLinkedCellsUsed(), true);
    EXPECT_NEAR(data.getLinkedCellsParameters()->getCutOffRadius(), 3.0, COMPARISON_TOLERANCE);

    auto boundaryMap = data.getBoundaryParameters()->getBoundaryMap();
    EXPECT_NEAR(data.getBoundaryParameters()->getDomain()[0], 180.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getBoundaryParameters()->getDomain()[1], 90.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getBoundaryParameters()->getDomain()[2], 3.0, COMPARISON_TOLERANCE);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::TOP], boundaries::BoundaryType::REFLECTING);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::RIGHT], boundaries::BoundaryType::OUTFLOW);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::BOTTOM], boundaries::BoundaryType::REFLECTING);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::LEFT], boundaries::BoundaryType::PERIODIC);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::FRONT], boundaries::BoundaryType::OFF);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::BACK], boundaries::BoundaryType::OFF);

    EXPECT_EQ(data.getParticleContainer()->getSize(), 0);
    EXPECT_EQ(data.getLinkedCellContainer()->getSize(), 25);
}

TEST(XMLReaderTest, ReadDiscFileLCTest) {
    const auto fileReader = std::make_unique<fileReaders::XMLReader>();
    SimulationDataContainer data = fileReader->readFile("./tests/io/in/XMLReaderTestLCDisc.xml");

    EXPECT_EQ(data.getFileWriterParameters()->getBaseName(), "testDisc");
    EXPECT_EQ(data.getFileWriterParameters()->getWriteFrequency(), 10);

    EXPECT_NEAR(data.getSimulationParameters()->getEnd_t(), 100.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getSimulationParameters()->getDelta_t(), 0.1, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getSimulationParameters()->getGravity(), -9.81, COMPARISON_TOLERANCE);
    EXPECT_EQ(data.getSimulationParameters()->getDimension(), 2);

    EXPECT_NEAR(data.getThermostatParameters()->getStartTemp(), 300.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getThermostatParameters()->getTargetTemp(), 300.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getThermostatParameters()->getMaxDeltaTemp(), 10.0, COMPARISON_TOLERANCE);
    EXPECT_EQ(data.getThermostatParameters()->getDimension(), 3);

    EXPECT_EQ(data.getLinkedCellsParameters()->isLinkedCellsUsed(), true);
    EXPECT_NEAR(data.getLinkedCellsParameters()->getCutOffRadius(), 3.0, COMPARISON_TOLERANCE);

    auto boundaryMap = data.getBoundaryParameters()->getBoundaryMap();
    EXPECT_NEAR(data.getBoundaryParameters()->getDomain()[0], 180.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getBoundaryParameters()->getDomain()[1], 90.0, COMPARISON_TOLERANCE);
    EXPECT_NEAR(data.getBoundaryParameters()->getDomain()[2], 3.0, COMPARISON_TOLERANCE);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::TOP], boundaries::BoundaryType::REFLECTING);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::RIGHT], boundaries::BoundaryType::OUTFLOW);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::BOTTOM], boundaries::BoundaryType::REFLECTING);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::LEFT], boundaries::BoundaryType::PERIODIC);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::FRONT], boundaries::BoundaryType::OFF);
    EXPECT_EQ(boundaryMap[boundaries::BoundaryDirection::BACK], boundaries::BoundaryType::OFF);

    EXPECT_EQ(data.getParticleContainer()->getSize(), 0);
    EXPECT_EQ(data.getLinkedCellContainer()->getSize(), 709);
}