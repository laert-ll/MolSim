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

TEST(ParticleContainerTest, IterateThroughParticles) {
    ParticleContainer pc_0;
    int expected_types_0[] = {};
    int index_0 = 0;
    for (auto it = pc_0.begin(); it != pc_0.end(); ++it) {
        FAIL() << "Loop should not run with 0 particles";
    }

    ParticleContainer pc_1;
    Particle p1(1);
    pc_1.addParticle(p1);

    int expected_types_1[] = {1};
    int index_1 = 0;
    for (auto it = pc_1.begin(); it != pc_1.end(); ++it) {
        EXPECT_EQ(it->getType(), expected_types_1[index_1]);
        ++index_1;
    }

    ParticleContainer pc_2;
    Particle p2(2);
    pc_2.addParticle(p1);
    pc_2.addParticle(p2);
    
    int expected_types_2[] = {1, 2};
    int index_2 = 0;
    for (auto it = pc_2.begin(); it != pc_2.end(); ++it) {
        EXPECT_EQ(it->getType(), expected_types_2[index_2]);
        ++index_2;
    }
}

TEST(ParticleContainerTest, IterateThroughPairs) {
    Particle p1(1);
    Particle p2(2);
    Particle p3(3);
    Particle p4(4);

    ParticleContainer pc_0;
    pc_0.initializePairs();
    EXPECT_EQ(pc_0.pair_begin(), pc_0.pair_end());

    ParticleContainer pc_1;
    pc_1.addParticle(p1);
    pc_1.initializePairs();
    EXPECT_EQ(pc_1.pair_begin(), pc_1.pair_end());

    ParticleContainer pc_2;
    pc_2.addParticle(p1);
    pc_2.addParticle(p2);
    pc_2.initializePairs();
    std::vector<std::pair<int, int>> expected_pairs_2 = {{1, 2}};
    auto expected_iter_2 = expected_pairs_2.begin();
    for (auto it = pc_2.pair_begin(); it != pc_2.pair_end(); ++it, ++expected_iter_2) {
        EXPECT_EQ(it->first.get().getType(), expected_iter_2->first);
        EXPECT_EQ(it->second.get().getType(), expected_iter_2->second);
    }

    ParticleContainer pc_3;
    pc_3.addParticle(p1);
    pc_3.addParticle(p2);
    pc_3.addParticle(p3);
    pc_3.initializePairs();
    std::vector<std::pair<int, int>> expected_pairs_3 = {{1, 2}, {1, 3}, {2, 3}};
    auto expected_iter_3 = expected_pairs_3.begin();
    for (auto it = pc_3.pair_begin(); it != pc_3.pair_end(); ++it, ++expected_iter_3) {
        EXPECT_EQ(it->first.get().getType(), expected_iter_3->first);
        EXPECT_EQ(it->second.get().getType(), expected_iter_3->second);
    }

    ParticleContainer pc_4;
    pc_4.addParticle(p1);
    pc_4.addParticle(p2);
    pc_4.addParticle(p3);
    pc_4.addParticle(p4);
    pc_4.initializePairs();
    std::vector<std::pair<int, int>> expected_pairs = {{1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}};
    auto expected_iter = expected_pairs.begin();
    for (auto it = pc_4.pair_begin(); it != pc_4.pair_end(); ++it, ++expected_iter) {
        EXPECT_EQ(it->first.get().getType(), expected_iter->first);
        EXPECT_EQ(it->second.get().getType(), expected_iter->second);
    }

    size_t expected_size = pc_4.getSize() * (pc_4.getSize() - 1) / 2;
    EXPECT_EQ(pc_4.pair_end() - pc_4.pair_begin(), expected_size);
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
