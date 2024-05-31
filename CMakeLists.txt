cmake_minimum_required(VERSION 3.10)
project(PSEMolDyn_GroupC VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
# ---------------------------------------- Dependencies -------------------------------------------------
# spdlog
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG v1.x
)
FetchContent_MakeAvailable(spdlog)
# gtest
FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
FetchContent_MakeAvailable(gtest)

# google benchmark
FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark
        GIT_TAG main
)
FetchContent_Declare(
        cxxopts
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts
        GIT_TAG        master
)
FetchContent_MakeAvailable(cxxopts)
include_directories(${cxxopts_SOURCE_DIR}/include)

FetchContent_MakeAvailable(benchmark)

# openmp (https://cliutils.gitlab.io/modern-cmake/chapters/packages/OpenMP.html)
find_package(OpenMP REQUIRED)
add_compile_options(-fopenmp)
# xerces-c
find_package(XercesC REQUIRED)
# libxsd (local)
include_directories(libs/libxsd)
# cxxopts(local)
include_directories(libs/cxxopts/include)
# ------------------------------------------------------------------------------------------------------------
include_directories(src)
set(SOURCES
        src/calculators/LJCalculator.cpp
        src/calculators/SVCalculator.cpp
        src/io/in/FileReader.cpp
        src/io/in/ParticleGenerator.cpp
        src/io/out/vtk-unstructured.cpp
        src/io/out/VTKWriter.cpp
        src/io/out/XYZWriter.cpp
        src/objects/Particle.cpp
        src/objects/ParticleContainer.cpp
        src/Boundaries/BoundaryHandler2D.cpp
        src/Boundaries/BoundaryController.cpp
)
set(TEST_SOURCES
        tests/calculators/CalculatorTest.cpp
        tests/calculators/LJCalculatorTest.cpp
        tests/calculators/SVCalculatorTest.cpp
        tests/io/in/FileReaderTest.cpp
        tests/io/in/ParticleGeneratorTest.cpp
        tests/objects/ParticleContainerTest.cpp
)

set(BENCHMARK_SOURCES
        benchmark/CalculatorLJBenchmark.cpp
)

#------------------------------------------LOGGING---------------------------------------------------------
# check if the log level is defined in the environment
if (DEFINED ENV{LOG_LEVEL})
    set(log_level $ENV{LOG_LEVEL})
else ()
    set(log_level "INFO")
endif ()
# define the valid log levels
set(valid_log_levels "TRACE" "DEBUG" "INFO" "WARN" "ERROR" "CRITICAL" "OFF")
# check if the log level is valid
if (NOT log_level IN_LIST valid_log_levels)
    message(FATAL_ERROR "Invalid log level: ${log_level}. Valid log levels are: ${valid_log_levels}")
endif ()
# define the SPDLOG_ACTIVE_LEVEL macro
add_compile_definitions(SPDLOG_ACTIVE_LEVEL=${log_level})
add_compile_definitions(LOG_LEVEL="${log_level}")
message(STATUS "Log level: ${log_level}")
#-----------------------------------------------------------------------------------------------------------
add_library(MolSimLib ${SOURCES})
target_link_libraries(MolSimLib
        XercesC::XercesC
        OpenMP::OpenMP_CXX
        spdlog::spdlog
        $<$<BOOL:${MINGW}>:ws2_32>
        gtest
)
# main
add_executable(MolSim src/Main.cpp)
target_link_libraries(MolSim MolSimLib)
# tests
add_executable(MolSimTests
        ${TEST_SOURCES}
        tests/MolSimTest.cpp
)
target_link_libraries(MolSimTests
        MolSimLib
        gtest
)
# benchmarks
add_executable(MolSimBenchmark
        ${BENCHMARK_SOURCES}
)
target_link_libraries(MolSimBenchmark
        MolSimLib
        benchmark
)

add_test(NAME MolSimTests COMMAND MolSimTests)

# activate all compiler warnings. Clean up your code :P
# depending on the compiler different flags are used
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
include(doxygen)
include(CTest)