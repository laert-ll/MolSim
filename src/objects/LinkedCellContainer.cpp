#include "LinkedCellContainer.h"
#include "Particle.h"
#include "Cell.h"
#include "../utils/MaxwellBoltzmannDistribution.h"
#include "spdlog/spdlog.h"

#include <cmath>

void LinkedCellContainer::initializeAndPopulateCells() {
    initializeCells();
    initializeNeighbors();
    populateCells();
}

void LinkedCellContainer::addParticle(const std::shared_ptr<Particle> &particle) {
    particles.push_back(particle);
}

std::vector<std::shared_ptr<Particle>>::iterator LinkedCellContainer::begin() {
    return particles.begin();
}

std::vector<std::shared_ptr<Particle>>::iterator LinkedCellContainer::end() {
    return particles.end();
}

std::vector<std::shared_ptr<Particle>> LinkedCellContainer::getParticles() const {
    return particles;
}

std::vector<std::vector<std::vector<std::shared_ptr<Cell>>>> LinkedCellContainer::getCells() {
    return cells;
}

size_t LinkedCellContainer::getSize() const {
    return particles.size();
}

void LinkedCellContainer::initializeCells() {
    size_t numCellsX = static_cast<size_t>(std::ceil(domain[0] / cellSize));
    size_t numCellsY = static_cast<size_t>(std::ceil(domain[1] / cellSize));
    size_t numCellsZ = static_cast<size_t>(std::ceil(domain[2] / cellSize));
    SPDLOG_DEBUG("Number of cells in x: {}, y: {}, z: {}", numCellsX, numCellsY, numCellsZ);

    const double lastCellSizeX = domain[0] - (cellSize * (numCellsX - 1));
    const double lastCellSizeY = domain[1] - (cellSize * (numCellsY - 1));
    const double lastCellSizeZ = domain[2] - (cellSize * (numCellsZ - 1));
    SPDLOG_DEBUG("Last cell size in x: {}, y: {}, z: {}", lastCellSizeX, lastCellSizeY, lastCellSizeZ);

    cells.resize(numCellsX);
    for (size_t x = 0; x < numCellsX; ++x) {
        cells[x].resize(numCellsY);
        for (size_t y = 0; y < numCellsY; ++y) {
            cells[x][y].resize(numCellsZ);
            for (size_t z = 0; z < numCellsZ; ++z) {
                const double cellSizeX = (x == numCellsX - 1) ? lastCellSizeX : cellSize;
                const double cellSizeY = (y == numCellsY - 1) ? lastCellSizeY : cellSize;
                const double cellSizeZ = (z == numCellsZ - 1) ? lastCellSizeZ : cellSize;
                cells[x][y][z] = std::make_shared<Cell>(x, y, z, cellSizeX, cellSizeY, cellSizeZ);
                SPDLOG_DEBUG("Created Cell at index ({}, {}, {}) with dimensions: {} x {} x {}",
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
                            const int neighborXIndex = x + cell->getIndex()[0];
                            const int neighborYIndex = y + cell->getIndex()[1];
                            const int neighborZIndex = z + cell->getIndex()[2];

                            if (neighborXIndex >= 0 && neighborXIndex < cells.size() &&
                                neighborYIndex >= 0 && neighborYIndex < cells[0].size() &&
                                neighborZIndex >= 0 && neighborZIndex < cells[0][0].size()) {
                                cell->addNeighbor(cells[neighborXIndex][neighborYIndex][neighborZIndex]);
                                SPDLOG_DEBUG("Cell at index ({}, {}, {}) has neighbor at index ({}, {}, {})",
                                             cell->getIndex()[0], cell->getIndex()[1], cell->getIndex()[2],
                                             neighborXIndex, neighborYIndex, neighborZIndex);
                            }
                        }
                    }
                }
            }
        }
    }
}

void LinkedCellContainer::populateCells() {
    for (auto &particle: particles) {
        auto position = particle->getX();
        SPDLOG_DEBUG("Particle at position ({}, {}, {})", position[0], position[1], position[2]);
        if (position[0] >= domain[0] || position[0] < 0 || position[1] >= domain[1] || position[1] < 0 ||
            position[2] >= domain[2] || position[2] < 0) {
            SPDLOG_ERROR("Particle at position ({}, {}, {}) is outside the domain ({},{})", position[0], position[1],
                         position[2], domain[0], domain[1]);
            exit(-1);
        }
        const std::array<size_t, 3> cellIndex = getCellIndex(particle);
        cells[cellIndex[0]][cellIndex[1]][cellIndex[2]]->addParticle(particle);
    }
    SPDLOG_INFO("Populated cells with particles");
}

std::vector<std::shared_ptr<Cell>> &LinkedCellContainer::getNeighboringCellsIncludingSelf(const Particle &particle) {
    const std::array<size_t, 3> cellIndex = getCellIndex(std::make_shared<Particle>(particle));
    return cells[cellIndex[0]][cellIndex[1]][cellIndex[2]]->getNeighboringCells();
}

void LinkedCellContainer::updateCells() {
    for (auto &row: cells) {
        for (auto &col: row) {
            for (auto &cell: col) {
                auto it = cell->getParticles().begin();
                while (it != cell->getParticles().end()) {
                    auto particleIndex = getCellIndex(*it);
                    if (!(cell->getIndex() == particleIndex)) {
                        cells[particleIndex[0]][particleIndex[1]][particleIndex[2]]->addParticle(*it);
                        SPDLOG_DEBUG("Moved particle to cell at index ({}, {}, {})", particleIndex[0], particleIndex[1],
                                     particleIndex[2]);
                        cell->removeParticle(*it);
                        SPDLOG_DEBUG("Removed particle from cell at index ({}, {}, {})", cell->getIndex()[0],
                                     cell->getIndex()[1], cell->getIndex()[2]);
                        it = cell->getParticles().begin(); // Reset the iterator as the set has been modified
                    } else {
                        ++it;
                    }
                }
            }
        }
    }
}

std::array<size_t, 3> LinkedCellContainer::getCellIndex(const std::shared_ptr<Particle> &particle) {
    return getCellIndex(particle->getX());
}

std::array<size_t, 3> LinkedCellContainer::getCellIndex(const std::array<double, 3> &positions) {
    size_t cellIndexX = static_cast<size_t>(positions[0] / cellSize);
    size_t cellIndexY = static_cast<size_t>(positions[1] / cellSize);
    size_t cellIndexZ = static_cast<size_t>(positions[2] / cellSize);
    SPDLOG_DEBUG("Particle at position ({}, {}, {}) is in cell ({}, {}, {}) with domain ({}, {}, {})", positions[0],
                 positions[1], positions[2],
                 cellIndexX, cellIndexY, cellIndexZ, domain[0], domain[1], domain[2]);
    return std::array<size_t, 3>{{cellIndexX, cellIndexY, cellIndexZ}};
}

void LinkedCellContainer::setCutOffRadius(const double &cutoffRadius) {
    this->cutoffRadius = cutoffRadius;
    SPDLOG_INFO("Set cutoff radius to {}", this->cutoffRadius);
}

void LinkedCellContainer::setCellSize(const double &cellSize) {
    this->cellSize = cellSize;
    SPDLOG_INFO("Set cell size to {}", this->cellSize);
}

bool LinkedCellContainer::hasZeroVelocities() {
    auto particles = this->getParticles();
    for (const auto &particle: this->particles) {
        if (!particle->hasZeroVelocities()) {
            return false;
        }
    }
    return true;
}

void LinkedCellContainer::setDomain(const std::array<double, 3> &domain) {
    this->domain = domain;
    SPDLOG_INFO("Set domain to ({}, {}, {})", domain[0], domain[1], domain[2]);
}

std::vector<std::shared_ptr<Cell>>
LinkedCellContainer::getBoundaryCells(const size_t &boundaryWidthInNumCells) {
    std::vector<std::shared_ptr<Cell>> boundaryCells;

    const size_t numCellsX = cells.size();
    const size_t numCellsY = cells[0].size();
    const size_t numCellsZ = cells[0][0].size();

    const bool is3D = numCellsZ > 1;

    for (size_t i = 0; i < numCellsX; ++i) {
        for (size_t j = 0; j < numCellsY; ++j) {
            for (size_t k = 0; k < numCellsZ; ++k) {
                bool isBoundaryX = i < boundaryWidthInNumCells || i >= numCellsX - boundaryWidthInNumCells;
                bool isBoundaryY = j < boundaryWidthInNumCells || j >= numCellsY - boundaryWidthInNumCells;
                bool isBoundaryZ = is3D && (k < boundaryWidthInNumCells || k >= numCellsZ - boundaryWidthInNumCells);

                if (isBoundaryX || isBoundaryY || isBoundaryZ) {
                    boundaryCells.push_back(cells[i][j][k]);
                }
            }
        }
    }

    return boundaryCells;
}

void LinkedCellContainer::removeParticle(const std::shared_ptr<Particle> &particle) {
    auto it = particles.begin();
    while (it != particles.end()) {
        if (*it == particle) {
            const std::array<size_t, 3> cellIndex = getCellIndex(particle);
            cells[cellIndex[0]][cellIndex[1]][cellIndex[2]]->removeParticle(particle);
            particles.erase(it);
            return;
        } else {
            ++it;
        }
    }
}
