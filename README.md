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

1. Create a build folder and enter it:

   `mkdir build && cd build`

2. Build the code:

   `cmake ../CMakeLists.txt`
   
   `make -j $(nproc)`

3. Run the code:

   `./MolSim`
