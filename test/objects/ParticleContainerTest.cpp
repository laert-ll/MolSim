#include "../../src/objects/ParticleContainer.h"
#include "../../src/objects/Particle.h"
#include "gtest/gtest.h"

TEST(ParticleContainerTest, AddParticleGetSize) {
    ParticleContainer pc;
    EXPECT_EQ(pc.getSize(), 0);

    Particle p1;
    Particle p2;
    pc.addParticle(p1);
    pc.addParticle(p2);
    EXPECT_EQ(pc.getSize(), 2);
}

TEST(ParticleContainerTest, InitializePairs) {
    ParticleContainer pc;
    Particle p1;
    Particle p2;
    Particle p3;
    pc.addParticle(p1);
    pc.addParticle(p2);
    pc.addParticle(p3);
    pc.initializePairs();
    size_t expected_pairs = pc.getSize() * (pc.getSize() - 1) / 2;
    EXPECT_EQ(pc.pair_end() - pc.pair_begin(), expected_pairs);
}

TEST(ParticleContainerTest, SetVolumes) {
    ParticleContainer pc;
    pc.addParticle(Particle({0, 0, 0}, {0, 0, 0}, 1.0, 0.0));
    pc.addParticle(Particle({0, 0, 0}, {0, 0, 0}, 3.0e-6, 0.0));
    pc.addParticle(Particle({0, 0, 0}, {0, 0, 0}, 9.55e-4, 0.0));
    pc.addParticle(Particle({0, 0, 0}, {0, 0, 0}, 1.0e-14, 0.0));
    pc.setVolumes();

    std::vector<double> expectedVolumes = {1.0, 0.500001, 0.500478, 0.5};

    auto expectedVolumeIter = expectedVolumes.begin();
    for (auto p = pc.begin(); p != pc.end(); ++p, ++expectedVolumeIter) {
        EXPECT_NEAR(p->getVolume(), *expectedVolumeIter, 1e-6);
    }
}