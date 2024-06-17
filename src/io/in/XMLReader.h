#pragma once

#include "CuboidParameters.h"
#include "FileReader.h"
#include <string>
#include <vector>
#include <array>

namespace fileReaders {

    class XMLReader {
    public:
        /**
         * Constructor to initialize the XMLReader
         */
        XMLReader() = default;

        /**
         * Read the XML file and load the parameters
         * @param filepath the path to the XML file
         */
        void readFileParameters(const std::string& filepath);

        /**
         * Getter for domain
         * @return the domain as an array of three doubles
         */
        std::array<double, 3> getDomain() const;

        /**
         * Getter for cutoffRadius
         * @return the cutoff radius
         */
        double getCutoffRadius() const;

        /**
         * Getter for deltaT
         * @return the delta time
         */
        double getDeltaT() const;

        /**
         * Getter for endTime
         * @return the end time
         */
        double getEndTime() const;

        /**
         * Getter for baseName
         * @return the base name as a string
         */
        std::string getBaseName() const;

        /**
         * Getter for writerFrequency
         * @return the writer frequency as an int
         */
        int getWriterFrequency() const;

        /**
         * Getter for cuboid parameters
         * @return a vector of CuboidParameters
         */
        std::vector<CuboidParameters> getCuboidParameters() const;

    private:
        std::array<double, 3> domain;
        double cutoffRadius;
        double delta_t;
        double end_time;
        std::string baseName;
        int writerFrequency;
        std::vector<CuboidParameters> cuboidParameters;
    };

}  // namespace fileReaders
