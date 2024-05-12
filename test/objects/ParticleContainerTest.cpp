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
    Particle p1(1);
    Particle p2(2);
    Particle p3(3);
    Particle p4(4);

    ParticleContainer pc_empty;
    pc_empty.initializePairs();
    EXPECT_EQ(pc_empty.pair_begin(), pc_empty.pair_end());

    ParticleContainer pc_one_particle;
    pc_one_particle.addParticle(p1);
    pc_one_particle.initializePairs();
    EXPECT_EQ(pc_one_particle.pair_begin(), pc_one_particle.pair_end());

    ParticleContainer pc_two_particles;
    pc_two_particles.addParticle(p1);
    pc_two_particles.addParticle(p2);
    pc_two_particles.initializePairs();
    std::vector<std::pair<int, int>> expected_pairs_two_particles = {{p1.getType(), p2.getType()}};
    auto pair_iter_two = pc_two_particles.pair_begin();
    for (const auto& expected_pair : expected_pairs_two_particles) {
        EXPECT_EQ(expected_pair.first, pair_iter_two->first.get().getType());
        EXPECT_EQ(expected_pair.second, pair_iter_two->second.get().getType());
        ++pair_iter_two;
    }

    ParticleContainer pc_four_particles;
    pc_four_particles.addParticle(p3);
    pc_four_particles.addParticle(p4);
    pc_four_particles.initializePairs();
    std::vector<std::pair<int, int>> expected_pairs_four_particles = {{p3.getType(), p4.getType()}};
    auto pair_iter_four = pc_four_particles.pair_begin();
    for (const auto& expected_pair : expected_pairs_four_particles) {
        EXPECT_EQ(expected_pair.first, pair_iter_four->first.get().getType());
        EXPECT_EQ(expected_pair.second, pair_iter_four->second.get().getType());
        ++pair_iter_four;
    }

    size_t expected_size = pc_four_particles.getSize() * (pc_four_particles.getSize() - 1) / 2;
    EXPECT_EQ(pc_four_particles.pair_end() - pc_four_particles.pair_begin(), expected_size);
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
