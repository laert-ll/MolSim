
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <list>

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
void calculateF();

/**
 * calculate the position for all particles
 */
void calculateX();

/**
 * calculate the position for all particles
 */
void calculateV();

/**
 * plot the particles to a xyz-file
 */
void plotParticles(int iteration);

constexpr double start_time = 0;
constexpr double end_time = 1000;
constexpr double delta_t = 0.014;

// TODO: what data structure to pick?
std::list<Particle> particles;

int main(int argc, char *argsv[]) {

  std::cout << "Hello from MolSim for PSE!" << std::endl;
  if (argc != 2) {
    std::cout << "Erroneous programme call! " << std::endl;
    std::cout << "./molsym filename" << std::endl;
  }

  FileReader fileReader;
  fileReader.readFile(particles, argsv[1]);

  double current_time = start_time;

  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
    while (current_time < end_time) {
    // calculate new x
    calculateX();
    // calculate new f
    calculateF();
    // calculate new v
    calculateV();

    iteration++;
    if (iteration % 10 == 0) {
      plotParticles(iteration);
    }
    std::cout << "Iteration " << iteration << " finished." << std::endl;

    current_time += delta_t;
  }

  std::cout << "output written. Terminating..." << std::endl;
  return 0;
}

void calculateF() {
  std::list<Particle>::iterator iterator;
  iterator = particles.begin();

  for (auto &p1 : particles) {
    for (auto &p2 : particles) {
      // @TODO: insert calculation of forces here!
    }
  }
}

void calculateX() {
  for (auto &p : particles) {
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

void calculateV() {
  for (auto &p : particles) {
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

void plotParticles(int iteration) {

  std::string out_name("MD_vtk");

  outputWriter::XYZWriter writer;
  writer.plotParticles(particles, out_name, iteration);
}
