#include "../src/objects/ParticleContainer.h"
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
    Particle p1;
    Particle p2;
    Particle p3;
    pc.addParticle(p1);
    pc.addParticle(p2);
    pc.addParticle(p3);
    EXPECT_EQ(pc.getSize(), 3);
}
