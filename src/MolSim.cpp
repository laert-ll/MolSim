
#include "FileReader.h"
#include "Calculator.h"

#include <iostream>
#include <list>

constexpr double start_time = 0;
constexpr double end_time = 1000;
constexpr double delta_t = 0.014;

int main(int argc, char *argsv[]) {

  std::cout << "Hello from MolSim for PSE!" << std::endl;
  if (argc != 2) {
    std::cout << "Erroneous programme call! " << std::endl;
    std::cout << "./molsym filename" << std::endl;
  }

  std::list<Particle> particles;

  FileReader fileReader;
  fileReader.readFile(particles, argsv[1]);

  Calculator calculator;

  double current_time = start_time;

  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
    while (current_time < end_time) {
        // calculate new x
        calculator.calculateX(particles, delta_t);
        // calculate new f
        calculator.calculateF(particles);
        // calculate new v
        calculator.calculateV(particles, delta_t);

    iteration++;
    if (iteration % 10 == 0) {
      calculator.plotParticles(iteration, particles);
    }
    std::cout << "Iteration " << iteration << " finished." << std::endl;

    current_time += delta_t;
  }

  std::cout << "output written. Terminating..." << std::endl;
  return 0;
}
