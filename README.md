# Molecular Dynamics - Group C

---

## Installation Instructions

This is the program frame for the Molecular Dynamics teaching code from Group C.

### Prerequisites

In order to build and run this code, you need the following tools installed on your PC:

- g++
- cmake
- libxerces-c-dev

### Build and Run

1. Create a `build` directory and enter it:

   `mkdir build && cd build`

2. Build the code:

   `cmake ../CMakeLists.txt`
3. Move to the project directory:

   `cd ..`
4. Make:

   `make -j $(nproc)`

   If you also wish to build the documentation, run:

   `make doc_doxygen`

3. Run the code:

   `./MolSim ../input/eingabe-sonne.txt {DELTA_T} {END_TIME} {TEST_ENABLED}`

   Example call: `./MolSim ./input/eingabe-sonne.txt 0.01 1 false` 
