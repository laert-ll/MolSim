#include "LinkedCellContainer.h"
#include "Particle.h"
#include "Cell.h"
#include "../utils/MaxwellBoltzmannDistribution.h"
#include "../utils/ArrayUtils.h"
#include "spdlog/spdlog.h"

#include <cmath>

LinkedCellContainer::LinkedCellContainer(std::array<double, 3> &domain, std::vector<CuboidParameters> &cuboidParameters,
                                         double &cutoffRadius, double &cellSize)
        : domain(domain), cutoffRadius(cutoffRadius), cellSize(cellSize) {
    initializeCells();
    initializeNeighbors();
    generateCuboids(cuboidParameters);
    populateCells();
}

void LinkedCellContainer::addParticle(const Particle &particle) {
    particles.push_back(particle);
}

std::vector<Particle>::iterator LinkedCellContainer::begin() {
    return particles.begin();
}

std::vector<Particle>::iterator LinkedCellContainer::end() {
    return particles.end();
}

std::vector<Particle> LinkedCellContainer::getParticles() const {
    return particles;
}

std::vector<std::vector<std::vector<Cell>>> LinkedCellContainer::getCells() {
    return cells;
}

size_t LinkedCellContainer::getSize() const {
    return particles.size();
}

void LinkedCellContainer::initializeCells() {
    size_t numCellsX = static_cast<size_t>(std::ceil(domain[0] / cellSize));
    size_t numCellsY = static_cast<size_t>(std::ceil(domain[1] / cellSize));
    size_t numCellsZ = static_cast<size_t>(std::ceil(domain[2] / cellSize));

    const double lastCellSizeX = domain[0] - (cellSize * (numCellsX - 1));
    const double lastCellSizeY = domain[1] - (cellSize * (numCellsY - 1));
    const double lastCellSizeZ = domain[2] - (cellSize * (numCellsZ - 1));

    cells.resize(numCellsX);
    for (size_t x = 0; x < numCellsX; ++x) {
        cells[x].resize(numCellsY);
        for (size_t y = 0; y < numCellsY; ++y) {
            cells[x][y].resize(numCellsZ);
            for (size_t z = 0; z < numCellsZ; ++z) {
                const double cellSizeX = (x == numCellsX - 1) ? lastCellSizeX : cellSize;
                const double cellSizeY = (y == numCellsY - 1) ? lastCellSizeY : cellSize;
                const double cellSizeZ = (z == numCellsZ - 1) ? lastCellSizeZ : cellSize;
                cells[x][y][z] = Cell(x, y, z, cellSizeX, cellSizeY, cellSizeZ);
                SPDLOG_INFO("Created Cell at index ({}, {}, {}) with dimensions: {} x {} x {}",
                            x, y, z, cellSizeX, cellSizeY, cellSizeZ);
            }
        }
    }

    SPDLOG_INFO("Created LinkedCellContainer with dimensions: {} x {} x {} and cell grid: {} x {} x {}",
                domain[0], domain[1], domain[2], numCellsX, numCellsY, numCellsZ);
}

void LinkedCellContainer::initializeNeighbors() {
    int cutoffRadiusIndex = static_cast<int>(std::ceil(cutoffRadius / cellSize)) + 1;

    for (auto &row: cells) {
        for (auto &col: row) {
            for (auto &cell: col) {
                for (int x = -cutoffRadiusIndex; x <= cutoffRadiusIndex; ++x) {
                    for (int y = -cutoffRadiusIndex; y <= cutoffRadiusIndex; ++y) {
                        for (int z = -cutoffRadiusIndex; z <= cutoffRadiusIndex; ++z) {
                            const int neighborXIndex = x + cell.getIndex()[0];
                            const int neighborYIndex = y + cell.getIndex()[1];
                            const int neighborZIndex = z + cell.getIndex()[2];

                            if (neighborXIndex >= 0 && neighborXIndex < cells.size() &&
                                neighborYIndex >= 0 && neighborYIndex < cells[0].size() &&
                                neighborZIndex >= 0 && neighborZIndex < cells[0][0].size()) {
                                cell.addNeighbor(&cells[neighborXIndex][neighborYIndex][neighborZIndex]);
                                SPDLOG_INFO("Cell at index ({}, {}, {}) has neighbor at index ({}, {}, {})",
                                            cell.getIndex()[0], cell.getIndex()[1], cell.getIndex()[2],
                                            neighborXIndex, neighborYIndex, neighborZIndex);
                            }
                        }
                    }
                }
            }
        }
    }
    /**
    for (auto &row: cells) {
        for (auto &col: row) {
            for (auto &cell: col) {
                SPDLOG_INFO("Cell at index ({}, {}, {}) has {} neighbors", cell.getIndex()[0], cell.getIndex()[1],
                            cell.getIndex()[2], cell.getNeighboringCellsSize());
            }
        }
    }
     **/

}

void LinkedCellContainer::generateCuboids(std::vector<CuboidParameters> &cuboidParameters) {
    for (const auto &cuboid: cuboidParameters) {
        const auto &lowerLeftFrontCorner = cuboid.lowerLeftFrontCorner;
        const auto &numParticlesPerDimension = cuboid.numParticlesPerDimension;
        const auto &distance = cuboid.distance;
        const auto &m = cuboid.m;
        const auto &startV = cuboid.startV;
        const auto &meanV = cuboid.meanV;

        for (std::size_t xIndex = 0; xIndex < numParticlesPerDimension[0]; ++xIndex) {
            for (std::size_t yIndex = 0; yIndex < numParticlesPerDimension[1]; ++yIndex) {
                for (std::size_t zIndex = 0; zIndex < numParticlesPerDimension[2]; ++zIndex) {
                    const std::array<double, 3> x = {
                            lowerLeftFrontCorner[0] + xIndex * distance,
                            lowerLeftFrontCorner[1] + yIndex * distance,
                            lowerLeftFrontCorner[2] + zIndex * distance
                    };
                    const std::array<double, 3> deltaV = maxwellBoltzmannDistributedVelocity(meanV, 2);
                    const std::array<double, 3> v = ArrayUtils::elementWisePairOp(startV, deltaV, std::plus<>());

                    Particle newParticle(x, v, m, 0, 0);
                    addParticle(newParticle);
                }
            }
        }

        SPDLOG_INFO(
                "Finished generating cuboid with LLF [{}, {}, {}], NumParticles [{}, {}, {}], Distance {}, Mass {}, StartV [{}, {}, {}], MeanV {}",
                lowerLeftFrontCorner[0], lowerLeftFrontCorner[1], lowerLeftFrontCorner[2], numParticlesPerDimension[0],
                numParticlesPerDimension[1],
                numParticlesPerDimension[2], distance, m, startV[0], startV[1], startV[2], meanV);
    }
    SPDLOG_INFO("Number of generated Particles: {}", particles.size());
}

void LinkedCellContainer::populateCells() {
    for (auto &particle: particles) {
        auto position = particle.getX();
        SPDLOG_INFO("Particle at position ({}, {}, {})", position[0], position[1], position[2]);
        if (position[0] >= domain[0] || position[0] < 0 || position[1] >= domain[1] || position[1] < 0 ||
            position[2] >= domain[2] || position[2] < 0) {
            SPDLOG_ERROR("Particle at position ({}, {}, {}) is outside the domain", position[0], position[1],
                         position[2]);
            exit(-1);
        }
        size_t cellIndexX = static_cast<size_t>(position[0] / cellSize);
        size_t cellIndexY = static_cast<size_t>(position[1] / cellSize);
        size_t cellIndexZ = static_cast<size_t>(position[2] / cellSize);
        cells[cellIndexX][cellIndexY][cellIndexZ].addParticle(&particle);
    }
    /**
    for (auto &row: cells) {
        for (auto &col: row) {
            for (auto &cell: col) {
                SPDLOG_INFO("Cell at index ({}, {}, {}) has {} particles", cell.getIndex()[0], cell.getIndex()[1],
                            cell.getIndex()[2], cell.getParticles().size());
            }
        }
    }
     **/
}

std::vector<std::shared_ptr<Cell>> &LinkedCellContainer::getNeighboringCellsIncludingSelf(const Particle &particle) {
    size_t cellIndexX = static_cast<size_t>(particle.getX()[0] / cellSize);
    size_t cellIndexY = static_cast<size_t>(particle.getX()[1] / cellSize);
    size_t cellIndexZ = static_cast<size_t>(particle.getX()[2] / cellSize);
    return cells[cellIndexX][cellIndexY][cellIndexZ].getNeighboringCells();
}

void LinkedCellContainer::update() {
    for (auto &row: cells) {
        for (auto &col: row) {
            for (auto &cell: col) {
                for (auto &particle: cell.getParticles()) {
                    auto particleIndex = getIndex(particle);
                    if (!(cell.getIndex() == particleIndex)) {
                        cells[particleIndex[0]][particleIndex[1]][particleIndex[2]].addParticle(particle);
                    }
                }
            }
        }
    }
}

std::array<size_t, 3> LinkedCellContainer::getIndex(std::shared_ptr<Particle>particle) {
    size_t cellIndexX = static_cast<size_t>(particle->getX()[0] / cellSize);
    size_t cellIndexY = static_cast<size_t>(particle->getX()[1] / cellSize);
    size_t cellIndexZ = static_cast<size_t>(particle->getX()[2] / cellSize);
    return std::array<size_t, 3>{{cellIndexX, cellIndexY, cellIndexZ}};
}
