#include "../../src/objects/LinkedCellContainer.h"
#include "../../src/objects/Particle.h"
#include "gtest/gtest.h"

TEST(LinkedCellContainerTest, AddParticleGetSize) {
    LinkedCellContainer lc;
    EXPECT_EQ(lc.getSize(), 0);

    auto p1 = std::make_shared<Particle>();
    auto p2 = std::make_shared<Particle>();
    lc.addParticle(p1);
    lc.addParticle(p2);
    EXPECT_EQ(lc.getSize(), 2);
}

TEST(LinkedCellContainerTest, IterateThroughParticles) {
    LinkedCellContainer lc_0;
    int expected_types_0[] = {};
    int index_0 = 0;
    for (auto it = lc_0.begin(); it != lc_0.end(); ++it) {
        FAIL() << "Loop should not run with 0 particles";
    }

    LinkedCellContainer lc_1;
    auto p1 = std::make_shared<Particle>(1);
    lc_1.addParticle(p1);

    int expected_types_1[] = {1};
    int index_1 = 0;
    for (auto &particle: lc_1) {
        EXPECT_EQ(particle->getType(), expected_types_1[index_1]);
    }

    LinkedCellContainer lc_2;
    auto p2 = std::make_shared<Particle>(2);
    lc_2.addParticle(p1);
    lc_2.addParticle(p2);
    
    int expected_types_2[] = {1, 2};
    int index_2 = 0;
    for (auto &particle: lc_2) {
        EXPECT_EQ(particle->getType(), expected_types_2[index_2]);
        ++index_2;
    }
}

TEST(LinkedCellContainerTest, RemoveParticleGetSize) {
    LinkedCellContainer lc;
    auto p1 = std::make_shared<Particle>();
    auto p2 = std::make_shared<Particle>();
    lc.addParticle(p1);
    lc.addParticle(p2);
    EXPECT_EQ(lc.getSize(), 2);

    lc.removeParticle(p1);
    EXPECT_EQ(lc.getSize(), 1);

    lc.removeParticle(p2);
    EXPECT_EQ(lc.getSize(), 0);
}

TEST(LinkedCellContainerTest, CheckParticlePositionInCells) {
    std::array<double, 3> domain = {120.0, 90.0, 3.0};
    double cutoffRadius = 3.0;
    double cellSize = 3.0;

    LinkedCellContainer lc;
    lc.setCellSize(cellSize);
    lc.setCutOffRadius(cutoffRadius);
    lc.setDomain(domain);

    auto p1 = std::make_shared<Particle>(1);
    p1->setX({1.5, 1.5, 1.5});
    lc.addParticle(p1);
    lc.initializeCells();
    lc.initializeNeighbors();
    lc.populateCells();

    auto cellIndex = lc.getCellIndex(p1->getX());
    auto cell = lc.getCells()[cellIndex[0]][cellIndex[1]][cellIndex[2]];
    auto particlesInCell = cell->getParticles();

    EXPECT_EQ(particlesInCell.size(), 1);
    EXPECT_EQ(particlesInCell.begin()->get()->getType(), 1);
}
