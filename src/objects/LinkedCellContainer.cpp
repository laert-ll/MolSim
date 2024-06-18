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
    int numCellsX = static_cast<int>(std::ceil(domain[0] / cellSize));
    int numCellsY = static_cast<int>(std::ceil(domain[1] / cellSize));
    int numCellsZ = static_cast<int>(std::ceil(domain[2] / cellSize));

    double lastCellSizeX = domain[0] - (cellSize * (numCellsX - 1));
    double lastCellSizeY = domain[1] - (cellSize * (numCellsY - 1));
    double lastCellSizeZ = domain[2] - (cellSize * (numCellsZ - 1));

    cells.resize(numCellsX);
    for (int x = 0; x < numCellsX; ++x) {
        cells[x].resize(numCellsY);
        for (int y = 0; y < numCellsY; ++y) {
            cells[x][y].resize(numCellsZ);
        }
    }
    for (int x = 0; x < numCellsX - 1; ++x) {
        for (int y = 0; y < numCellsY - 1; ++y) {
            for (int z = 0; z < numCellsZ - 1; ++z) {
                cells[x][y][z] = Cell(x, y, z, cellSize, cellSize, cellSize);
            }
        }
    }
    for (int y = 0; y < numCellsY; ++y) {
        for (int z = 0; z < numCellsZ; ++z) {
            cells[numCellsX - 1][y][z] = Cell(numCellsX - 1, y, z, lastCellSizeX, cellSize, cellSize);
        }
    }
    for (int x = 0; x < numCellsX; ++x) {
        for (int z = 0; z < numCellsZ; ++z) {
            cells[x][numCellsY - 1][z] = Cell(x, numCellsY - 1, z, cellSize, lastCellSizeY, cellSize);
        }
    }
    for (int x = 0; x < numCellsX; ++x) {
        for (int y = 0; y < numCellsY; ++y) {
            cells[x][y][numCellsZ - 1] = Cell(x, y, numCellsZ - 1, cellSize, cellSize, lastCellSizeZ);
        }
    }
    cells[numCellsX - 1][numCellsY - 1][numCellsZ - 1] = Cell(numCellsX - 1, numCellsY - 1, numCellsZ - 1,
                                                              lastCellSizeX, lastCellSizeY, lastCellSizeZ);
    SPDLOG_INFO("Created LinkedCellContainer with (cell) dimensions: {} x {} x {}", numCellsX, numCellsY, numCellsZ);

}

void LinkedCellContainer::initializeNeighbors() {
    int cutoffRadiusIndex = static_cast<int>(std::ceil(cutoffRadius / cellSize)) + 1;

    for (auto &row: cells) {
        for (auto &col: row) {
            for (auto &cell: col) {
                for (int x = -cutoffRadiusIndex; x <= cutoffRadiusIndex; ++x) {
                    for (int y = -cutoffRadiusIndex; y <= cutoffRadiusIndex; ++y) {
                        for (int z = -cutoffRadiusIndex; z <= cutoffRadiusIndex; ++z) {
                            if (x == 0 && y == 0 && z == 0) {
                                continue;
                            }
                            int neighborXIndex = x + static_cast<int>(std::floor(domain[0] / cellSize));
                            int neighborYIndex = y + static_cast<int>(std::floor(domain[1] / cellSize));
                            int neighborZIndex = z + static_cast<int>(std::floor(domain[2] / cellSize));

                            if (neighborXIndex >= 0 && neighborXIndex < cells.size() &&
                                neighborYIndex >= 0 && neighborYIndex < cells[0].size() &&
                                neighborZIndex >= 0 && neighborZIndex < cells[0][0].size()) {
                                cell.addNeighbor(&cells[neighborXIndex][neighborYIndex][neighborZIndex]);
                            }
                        }
                    }
                }
            }
        }
    }

    for (auto &row: cells) {
        for (auto &col: row) {
            for (auto &cell: col) {
                SPDLOG_INFO("Cell at index ({}, {}, {}) has {} neighbors", cell.getIndex()[0], cell.getIndex()[1],
                            cell.getIndex()[2], cell.getNeighboringCellsSize());
            }
        }
    }

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

        SPDLOG_INFO("Finished generating cuboid with LLF [{}, {}, {}], NumParticles [{}, {}, {}], Distance {}, Mass {}, StartV [{}, {}, {}], MeanV {}",
                    lowerLeftFrontCorner[0], lowerLeftFrontCorner[1], lowerLeftFrontCorner[2], numParticlesPerDimension[0], numParticlesPerDimension[1],
                    numParticlesPerDimension[2], distance, m, startV[0], startV[1], startV[2], meanV);
    }
    SPDLOG_INFO("Number of generated Particles: {}", particles.size());
}

void LinkedCellContainer::populateCells() {
    for (auto &particle: particles) {
        auto position = particle.getX();
        int cellIndexX = static_cast<int>(position[0] / cellSize);
        int cellIndexY = static_cast<int>(position[1] / cellSize);
        int cellIndexZ = static_cast<int>(position[2] / cellSize);
        cells[cellIndexX][cellIndexY][cellIndexZ].addParticle(&particle);
    }
    for (auto &row: cells) {
        for (auto &col: row) {
            for (auto &cell: col) {
                SPDLOG_INFO("Cell at index ({}, {}, {}) has {} particles", cell.getIndex()[0], cell.getIndex()[1],
                            cell.getIndex()[2], cell.getParticles().size());
            }
        }
    }
}

std::vector<Cell *> &LinkedCellContainer::getNeighboringCells(const Particle &particle) {
    int cellIndexX = static_cast<int>(particle.getX()[0] / cellSize);
    int cellIndexY = static_cast<int>(particle.getX()[1] / cellSize);
    int cellIndexZ = static_cast<int>(particle.getX()[2] / cellSize);
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

std::array<int, 3> LinkedCellContainer::getIndex(Particle *particle) {
    int cellIndexX = static_cast<int>(particle->getX()[0] / cellSize);
    int cellIndexY = static_cast<int>(particle->getX()[1] / cellSize);
    int cellIndexZ = static_cast<int>(particle->getX()[2] / cellSize);
    return std::array<int, 3>{{cellIndexX, cellIndexY, cellIndexZ}};
}
