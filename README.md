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

3. Make:

   `make -j $(nproc)`

   If you also wish to build the documentation, run:

   `make doc_doxygen`

4. Run the code:

   `./MolSim ../input/eingabe-sonne.txt {DELTA_T} {END_TIME} {TEST_ENABLED} {OUTPUT_WRITER} {CALCULATOR}`

   Example call: `./MolSim ../input/eingabe-sonne.txt 0.01 1 false vtk sv`
5. Available options for arguments:

   `{DELTA_T}`: The time step for the simulation. It should be a positive number.

   `{END_TIME}`: The end time of the simulation. It should be a positive number.

   `{TEST_ENABLED}`: Whether to run tests. Available options are true or false.

   `{OUTPUT_WRITER}`: The output writer to use. Available options are vtk or xyz.

   `{CALCULATOR}`: The calculator to use. Available options are sv or dummy.
