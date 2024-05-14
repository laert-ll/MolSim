file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(RunTests ${TEST_SOURCES})

target_link_libraries(RunTests PRIVATE gtest gtest_main)

add_test(NAME MyTest COMMAND RunTests)
