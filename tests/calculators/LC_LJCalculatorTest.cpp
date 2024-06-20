#include "../../src/calculators/Calculator.h"
#include "../../src/calculators/LC_LJCalculator.h"
#include "../../src/objects/Particle.h"
#include "../../src/objects/LinkedCellContainer.h"
#include "gtest/gtest.h"

namespace {
    const auto calculator = std::make_unique<calculators::LC_LJCalculator>();
}

TEST(LC_LJCalculatorTest, CalculateFTest) {    
    std::array<double, 3> domain = {12.0, 9.0, 3.0};
    double cutoffRadius = 3.0;
    double cellSize = 3.0;
    LinkedCellContainer lc;
    lc.setCellSize(cellSize);
    lc.setCutOffRadius(cutoffRadius);
    lc.setDomain(domain);
    auto p1 = std::make_shared<Particle>(std::array<double, 3>{0.25, 0.25, 0.25}, std::array<double, 3>{0, 0, 0}, 1.0, 0.0, 0);
    auto p2 = std::make_shared<Particle>(std::array<double, 3>{1.25, 1.25, 1.25}, std::array<double, 3>{0, 0, 0}, 1.0, 0.0, 0);
    lc.addParticle(p1);
    lc.addParticle(p2);
    lc.initializeAndPopulateCells();

    calculator->calculateLC_F(lc);

    const std::vector<std::array<double, 3>> expectedForces = {
        {2.743, 2.743, 2.743},
        {-2.743, -2.743, -2.743}
    };

    int index = 0;
    for (auto &particle: lc) {
        std::array<double, 3> expectedF = expectedForces[index];
        std::array<double, 3> actualF = particle->getF();
        EXPECT_NEAR(expectedF[0], actualF[0], 1e-3);
        EXPECT_NEAR(expectedF[1], actualF[1], 1e-3);
        EXPECT_NEAR(expectedF[2], actualF[2], 1e-3);
        index++;
    }
}

TEST(LC_LJCalculatorTest, DifferentSigma) {
    std::array<double, 3> domain = {12.0, 9.0, 3.0};
    double cutoffRadius = 3.0;
    double cellSize = 3.0;
    LinkedCellContainer lc;
    lc.setCellSize(cellSize);
    lc.setCutOffRadius(cutoffRadius);
    lc.setDomain(domain);
    auto p1 = std::make_shared<Particle>(std::array<double, 3>{1.0, 0.0, 0.0}, std::array<double, 3>{0, 0, 0}, 1.0, 0.0, 1, 2.5, 5.0);
    auto p2 = std::make_shared<Particle>(std::array<double, 3>{2.0, 0.0, 0.0}, std::array<double, 3>{0, 0, 0}, 1.0, 0.0, 1, 3.5, 5.0);
    lc.addParticle(p1);
    lc.addParticle(p2);
    lc.initializeAndPopulateCells();

    calculator->calculateLC_F(lc);

    const std::vector<std::array<double, 3>> expectedForces = {
        {-254916720.0, 0.0, 0.0},
        {254916720.0, 0.0, 0.0}
    };

    int index = 0;
    for (auto &particle: lc) {
        std::array<double, 3> expectedF = expectedForces[index];
        std::array<double, 3> actualF = particle->getF();
        EXPECT_NEAR(expectedF[0], actualF[0], 1e-3);
        EXPECT_NEAR(expectedF[1], actualF[1], 1e-3);
        EXPECT_NEAR(expectedF[2], actualF[2], 1e-3);
        index++;
    }
}


TEST(LC_LJCalculatorTest, DifferentEpsilon) {
    std::array<double, 3> domain = {12.0, 9.0, 3.0};
    double cutoffRadius = 3.0;
    double cellSize = 3.0;
    LinkedCellContainer lc;
    lc.setCellSize(cellSize);
    lc.setCutOffRadius(cutoffRadius);
    lc.setDomain(domain);
    auto p1 = std::make_shared<Particle>(std::array<double, 3>{1.0, 0.0, 0.0}, std::array<double, 3>{0, 0, 0}, 1.0, 0.0, 0, 3.0, 2.0);
    auto p2 = std::make_shared<Particle>(std::array<double, 3>{2.0, 0.0, 0.0}, std::array<double, 3>{0, 0, 0}, 1.0, 0.0, 0, 3.0, 12.5);
    lc.addParticle(p1);
    lc.addParticle(p2);
    lc.initializeAndPopulateCells();

    calculator->calculateLC_F(lc);

    const std::vector<std::array<double, 3>> expectedForces = {
        {-254916720.0, 0.0, 0.0},
        {254916720.0, 0.0, 0.0}
    };

    int index = 0;
    for (auto &particle: lc) {
        std::array<double, 3> expectedF = expectedForces[index];
        std::array<double, 3> actualF = particle->getF();
        EXPECT_NEAR(expectedF[0], actualF[0], 1e-3);
        EXPECT_NEAR(expectedF[1], actualF[1], 1e-3);
        EXPECT_NEAR(expectedF[2], actualF[2], 1e-3);
        index++;
    }
}
