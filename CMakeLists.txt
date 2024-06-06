cmake_minimum_required(VERSION 3.10)

# Enable the FetchContent module
include(FetchContent)

# define project name, version
project(PSEMolDyn_GroupC VERSION 0.0.1)

# let ccmake and cmake-gui offer the default build type options
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo;MinSizeRel")

# set Release as the default build type if it is not yet set.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# ----------------------------------------Adding Libraries-------------------------------------------------
# Fetch spdlog from GitHub
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG        v1.x
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts
    GIT_TAG        master
)
FetchContent_MakeAvailable(cxxopts)

FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        main
)
FetchContent_MakeAvailable(gtest)

FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark
        GIT_TAG        main
)
FetchContent_MakeAvailable(benchmark)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
# ------------------------------------------------------------------------------------------------------------

# collect all cpp files
file(GLOB_RECURSE MY_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

file(GLOB_RECURSE TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/**/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/**/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/io/in/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/objects/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/calculators/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/boundaries/*.cpp"
)

file(GLOB_RECURSE BENCHMARK_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/objects/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/objects/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/io/in/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/io/in/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/calculators/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/calculators/*.h"
)

#------------------------------------------LOGGING---------------------------------------------------------
# check if the log level is defined in the environment
if(DEFINED ENV{LOG_LEVEL})
    set(log_level $ENV{LOG_LEVEL})
else()
    set(log_level "INFO")
endif()

# define the valid log levels
set(valid_log_levels "TRACE" "DEBUG" "INFO" "WARN" "ERROR" "CRITICAL" "OFF")

# check if the log level is valid
if(NOT log_level IN_LIST valid_log_levels)
    message(FATAL_ERROR "Invalid log level: ${log_level}. Valid log levels are: ${valid_log_levels}")
endif()

# define the SPDLOG_ACTIVE_LEVEL macro
add_compile_definitions(SPDLOG_ACTIVE_LEVEL=${log_level})
add_compile_definitions(LOG_LEVEL="${log_level}")
message(STATUS "Log level: ${log_level}")
#-----------------------------------------------------------------------------------------------------------
# create make target
add_executable(MolSim ${MY_SRC})
add_executable(MolSimTests ${TEST_SOURCES})
add_executable(MolSimBenchmark ${BENCHMARK_SOURCES})

# set cxx standard. You may raise this if you want.
target_compile_features(MolSim
        PRIVATE
            cxx_std_17
)

target_include_directories(MolSim
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/libxsd
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_include_directories(MolSimTests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_include_directories(MolSimBenchmark
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/benchmark
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(MolSim
        # stuff that is used in headers and source files
        PUBLIC
            xerces-c
        PRIVATE
            spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
            gtest
            gtest_main
            cxxopts
)

target_link_libraries(MolSimTests
         PRIVATE
            gtest
            gtest_main
            spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)

target_link_libraries(MolSimBenchmark
        PRIVATE
            benchmark
            spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
            gtest
            gtest_main
)

add_test(NAME MolSimTests COMMAND MolSimTests)

# activate all compiler warnings. Clean up your code :P
# depending on the compiler different flags are used
target_compile_options(MolSim
        PRIVATE
            $<$<CXX_COMPILER_ID:Clang>:-Wall -fopenmp>
)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

include(doxygen)
include(CTest)