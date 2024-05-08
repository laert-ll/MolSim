#include "../src/objects/ParticleContainer.h"
#include "../src/objects/Particle.h"
#include "gtest/gtest.h"

TEST(CalculatorTest, Positions) {
    ParticleContainer pc;
    pc.addParticle(Particle({1, 1, 1}, {0, 0, 0}, 1.0, 0.0));
    pc.addParticle(Particle({-1, -1, -1}, {0, 0, 0}, 1.0, 0.0));
    pc.initializePairs();
    pc.setVolumes();
    EXPECT_EQ(pc.getSize(), 2);
}
