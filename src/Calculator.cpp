//
// Created by kimj2 on 24.04.2024.
//

#include "Calculator.h"
#include <cmath>
#include "outputWriter/XYZWriter.h"
#include <list>

Calculator::Calculator() {
}

void Calculator::calculateF(std::list<Particle> &particles) {
    for (auto &p: particles) {
        // Update oldF with currentF
        p.setOldF(p.getF());
        p.setF({0, 0, 0}); // Reset F to zeros
    }

    // Iterate over all unique pairs of particles
    for (auto iter1 = particles.begin(); iter1 != particles.end(); ++iter1) {
        for (auto iter2 = std::next(iter1); iter2 != particles.end(); ++iter2) {
            // Get the positions and masses of the two particles
            std::array<double, 3> x1 = iter1->getX();
            std::array<double, 3> x2 = iter2->getX();
            double m1 = iter1->getM();
            double m2 = iter2->getM();

            // Calculate the distance vector and its norm
            std::array<double, 3> dx = {x2[0] - x1[0], x2[1] - x1[1], x2[2] - x1[2]};
            double distance = std::sqrt(dx[0] * dx[0] + dx[1] * dx[1] + dx[2] * dx[2]);

            // Calculate the force between the two particles
            std::array<double, 3> force = {(m1 * m2 / std::pow(distance, 3)) * dx[0],
                                           (m1 * m2 / std::pow(distance, 3)) * dx[1],
                                           (m1 * m2 / std::pow(distance, 3)) * dx[2]};

            // Add the force to the first particle and subtract it from the second particle (Newton's Third Law)
            std::array<double, 3> f1 = iter1->getOldF();
            std::array<double, 3> f2 = iter2->getOldF();
            iter1->setF({f1[0] + force[0], f1[1] + force[1], f1[2] + force[2]});
            iter2->setF({f2[0] - force[0], f2[1] - force[1], f2[2] - force[2]});
        }
    }

}

void Calculator::calculateX(std::list<Particle> &particles, double delta_t) {
    for (auto &p: particles) {
        // Get the current position, velocity, and force of the particle
        std::array<double, 3> x = p.getX();
        std::array<double, 3> v = p.getV();
        std::array<double, 3> f = p.getF();
        double m = p.getM();

        // Calculate the acceleration
        std::array<double, 3> a = {f[0] / m, f[1] / m, f[2] / m};

        // Update the position using the Velocity-Störmer-Verlet algorithm
        x[0] += delta_t * v[0] + (delta_t * delta_t / 2) * a[0];
        x[1] += delta_t * v[1] + (delta_t * delta_t / 2) * a[1];
        x[2] += delta_t * v[2] + (delta_t * delta_t / 2) * a[2];

        // Update the particle's position
        p.setX(x);
    }
}

void Calculator::calculateV(std::list<Particle> &particles, double delta_t) {
    for (auto &p: particles) {
        // Get the current velocity and force of the particle
        std::array<double, 3> v = p.getV();
        std::array<double, 3> f = p.getF();
        std::array<double, 3> old_f = p.getOldF();
        double m = p.getM();

        // Calculate the average force
        std::array<double, 3> avg_f = {(f[0] + old_f[0]) / 2, (f[1] + old_f[1]) / 2, (f[2] + old_f[2]) / 2};

        // Update the velocity using the Velocity-Störmer-Verlet algorithm
        v[0] += delta_t * avg_f[0] / m;
        v[1] += delta_t * avg_f[1] / m;
        v[2] += delta_t * avg_f[2] / m;

        // Update the particle's velocity
        p.setV(v);
    }
}

void Calculator::plotParticles(int iteration, std::list<Particle> &particles) {

    std::string out_name("MD_vtk");

    outputWriter::XYZWriter writer;
    writer.plotParticles(particles, out_name, iteration);
}