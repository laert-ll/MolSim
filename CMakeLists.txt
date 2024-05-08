cmake_minimum_required(VERSION 3.10)

# define project name, version
project(PSEMolDyn_GroupC VERSION 0.0.1)

# let ccmake and cmake-gui offer the default build type options
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo;MinSizeRel")

# set Release as the default build type if it is not yet set.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

add_subdirectory(gtest)

# collect all cpp files
file(GLOB_RECURSE MY_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

file(GLOB_RECURSE TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/objects/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/calculators/*.cpp"
)

# create make target
add_executable(MolSim ${MY_SRC})

add_executable(MolSimTests ${TEST_SOURCES})

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
        ${CMAKE_CURRENT_SOURCE_DIR}/test
)

target_link_libraries(MolSim
        # stuff that is used in headers and source files
        PUBLIC
            xerces-c
)

target_link_libraries(MolSimTests 
        PRIVATE 
            gtest 
            gtest_main
)

add_test(NAME MolSimTests COMMAND MolSimTests)

# activate all compiler warnings. Clean up your code :P
# depending on the compiler different flags are used
target_compile_options(MolSim
        PRIVATE
            $<$<CXX_COMPILER_ID:GNU>:-Wall>
            # disable some spam warnings for icpc...
            $<$<CXX_COMPILER_ID:Intel>:-w3 -wd383,981,1418,1572,2259>
)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

include(doxygen)
include(CTest)