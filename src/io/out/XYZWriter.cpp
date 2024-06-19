/*
 * XYZWriter.cpp
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#include "XYZWriter.h"
#include <iomanip>
#include <sstream>

namespace outputWriters {

    void XYZWriter::plotParticles(int iteration, ParticleContainer &particleContainer, const std::string &filename) {
        std::ofstream file;
        std::stringstream strstr;
        strstr << filename << "_" << std::setfill('0') << std::setw(4) << iteration << ".xyz";

        file.open(strstr.str().c_str());
        file << particleContainer.getSize() << std::endl;
        file << "Generated by MolSim. See http://openbabel.org/wiki/XYZ_(format) for "
                "file format doku."
             << std::endl;

        for (auto p = particleContainer.begin(); p != particleContainer.end(); ++p) {
            std::array<double, 3> x = p->getX();
            file << "Ar ";
            file.setf(std::ios_base::showpoint);

            for (auto &xi : x) {
                file << xi << " ";
            }

            file << std::endl;
        }

        file.close();
    }


    void XYZWriter::plotParticlesLC(int iteration, LinkedCellContainer &linkedCellContainer, const std::string &filename) {}

} // namespace outputWriters