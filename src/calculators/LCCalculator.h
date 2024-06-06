#pragma once

#include "../objects/ParticleContainer.h"
#include "Calculator.h"


namespace calculators {
    class LCCalculator : public Calculator {

        private:
            const double sigma;
            const double epsilon;
            const double threshold;

        public:
            LCCalculator(double sigma, double epsilon, double threshold) : sigma(sigma), epsilon(epsilon), threshold(threshold) {}

            void calculateF(ParticleContainer &particleContainer);
    };
}
