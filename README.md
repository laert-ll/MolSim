# Molecular Dynamics - Group C

---

## Installation Instructions

### Prerequisites

In order to build and run this code, you need the following tools installed on your PC:

- g++
- cmake
- libxerces-c-dev

### Build and Run

1. Create a `build` directory and enter it:

   `mkdir build && cd build`

2. Build the code:

   `cmake ..`
   
   The default log level is `INFO`.
   
    If you wish to set the log level manually, run:
   `LOG_LEVEL={WANTED_LOG_LEVEL} cmake ..`

   Valid log levels are: `TRACE`, `DEBUG`, `INFO`, `WARN`, `ERROR`, `CRITICAL`, `OFF`.
   

3. Make:

   `make -j $(nproc)`

   If you also wish to build the documentation, run:

   `make doc_doxygen`

4. Run the code:

   `./MolSim {INPUT} {DELTA_T} {END_TIME} {OUTPUT_WRITER} {CALCULATOR}`

   Example calls: 
      - `./MolSim --help`
      - `./MolSim --input=../resources/input-sun.txt --delta_t=0.014 --end_time=1000 --output=vtk --calculator=sv`
      - `./MolSim --input=../resources/input-cuboid.txt --delta_t=0.0002 --end_time=5 --output=vtk --calculator=lj --boundaries=2121`

5. Available options for arguments:

   `{HELP}`: Prints out a list of available options for arguments.

   `{INPUT}`: The txt file to be read as input for the file reader.

   `{DELTA_T}`: The time step for the simulation. It should be a positive number.

   `{END_TIME}`: The end time of the simulation. It should be a positive number.

   `{OUTPUT_WRITER}`: The output writer to use. Available options are vtk or xyz.

   `{CALCULATOR}`: The calculator to use. Available options are sv, lj or dummy.

   `{BOUNDARIES}`: The types of boundaries to apply. Use the following format: Left, Bottom, Right, Top.
   - 0: No boundary (off)
   - 1: Reflecting boundary
   - 2: Outflow boundary

6. If you wish to execute the tests:
      - `./MolSimTests`
      or
      - `ctest -V -R '.*Test'`

7. If you wish to execute the benchmarks:
      - `./MolSimBenchmark`
