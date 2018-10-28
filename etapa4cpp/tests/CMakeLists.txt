cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
file(GLOB source_files
        "../src/*.cpp"
        "../src/*.c"
        "../include/*.h"
)
file(GLOB test_files
        "unit/*.cpp"
)
add_executable(runTests ${source_files} ${test_files})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
