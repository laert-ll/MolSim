#include "../src/objects/ParticleContainer.h"
#include "../src/objects/Particle.h"
#include "gtest/gtest.h"

TEST(ParticleContainerTest, AddParticle) {
    ParticleContainer pc;
    Particle p;
    pc.addParticle(p);
    EXPECT_EQ(pc.getSize(), 1);
}
