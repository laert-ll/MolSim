#include "../src/objects/ParticleContainer.h"
#include "../src/objects/ParticleContainer.cpp"
#include "../src/objects/Particle.cpp"
#include "../src/objects/Particle.h"
#include "gtest/gtest.h"

TEST(ParticleContainerTest, AddParticle) {
    ParticleContainer pc;
    Particle p;
    pc.addParticle(p);
    EXPECT_EQ(pc.getSize(), 1);
}

TEST(ParticleContainerTest, GetSize) {
    ParticleContainer pc;
    Particle p1, p2;
    pc.addParticle(p1);
    pc.addParticle(p2);
    EXPECT_EQ(pc.getSize(), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
