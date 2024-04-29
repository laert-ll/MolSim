#include "Calculator.h"
#include "outputWriter/VTKWriter.h"

#include <cmath>

Calculator::Calculator() {
}

void Calculator::calculate(ParticleContainer &particleContainer, double delta_t) {
    calculateX(particleContainer, delta_t);
    calculateF(particleContainer);
    calculateV(particleContainer, delta_t);
}

void Calculator::calculateF(ParticleContainer &particleContainer) {
    for (auto p = particleContainer.begin(); p != particleContainer.end(); ++p) {
        p->setOldF(p->getF());  // Update oldF with currentF
        p->setF({0, 0, 0});     // Reset F to zeros
    }

    // Iterate over all unique pairs of particles
    for (auto pair = particleContainer.pair_begin(); pair != particleContainer.pair_end(); ++pair) {
        // Get the positions and masses of the two particles
        std::array<double, 3> x1 = pair->first.get().getX();
        std::array<double, 3> x2 = pair->second.get().getX();

        double m1 = pair->first.get().getM();
        double m2 = pair->second.get().getM();

        // Calculate the distance vector and its norm
        std::array<double, 3> dx = {x2[0] - x1[0], x2[1] - x1[1], x2[2] - x1[2]};
        double distance = std::sqrt(dx[0] * dx[0] + dx[1] * dx[1] + dx[2] * dx[2]);

        // Calculate the force between the two particles
        std::array<double, 3> force = {(m1 * m2 / std::pow(distance, 3)) * dx[0],
                                       (m1 * m2 / std::pow(distance, 3)) * dx[1],
                                       (m1 * m2 / std::pow(distance, 3)) * dx[2]};

        // Add the force to the first particle and subtract it from the second particle (Newton's Third Law)
        std::array<double, 3> f1 = pair->first.get().getF();
        std::array<double, 3> f2 = pair->second.get().getF();
        pair->first.get().setF({f1[0] + force[0], f1[1] + force[1], f1[2] + force[2]});
        pair->second.get().setF({f2[0] - force[0], f2[1] - force[1], f2[2] - force[2]});
    }
}

void Calculator::calculateX(ParticleContainer &particleContainer, double delta_t) {
    for (auto p = particleContainer.begin(); p != particleContainer.end(); ++p) {
        // Get the current position, velocity, force and mass of the particle
        std::array<double, 3> x = p->getX();
        std::array<double, 3> v = p->getV();
        std::array<double, 3> f = p->getF();

        double m = p->getM();

        // Calculate the acceleration
        std::array<double, 3> a = {f[0] / m, f[1] / m, f[2] / m};

        // Update the particles new position using the Velocity-Störmer-Verlet method
        x[0] += delta_t * v[0] + (delta_t * delta_t / 2) * a[0];
        x[1] += delta_t * v[1] + (delta_t * delta_t / 2) * a[1];
        x[2] += delta_t * v[2] + (delta_t * delta_t / 2) * a[2];

        p->setX(x);
    }
}

void Calculator::calculateV(ParticleContainer &particleContainer, double delta_t) {
    for (auto p = particleContainer.begin(); p != particleContainer.end(); ++p) {
        // Get the current position, velocity, force and mass of the particle
        std::array<double, 3> v = p->getV();
        std::array<double, 3> f = p->getF();
        std::array<double, 3> old_f = p->getOldF();
        double m = p->getM();

        // Calculate the average force
        std::array<double, 3> avg_f = {(f[0] + old_f[0]) / 2, (f[1] + old_f[1]) / 2, (f[2] + old_f[2]) / 2};

        // Update the particles new velocity using the Velocity-Störmer-Verlet method
        v[0] += (delta_t * avg_f[0]) / m;
        v[1] += (delta_t * avg_f[1]) / m;
        v[2] += (delta_t * avg_f[2]) / m;

        p->setV(v);
    }
}

void Calculator::plotParticles(int iteration, ParticleContainer &particleContainer) {
    std::string out_name("MD_vtk");
    outputWriter::VTKWriter writer;
    writer.initializeOutput(particleContainer.getSize());

    for (auto p = particleContainer.begin(); p != particleContainer.end(); ++p) {
        writer.plotParticle(*p);
    }

    writer.writeFile(out_name, iteration);
}

