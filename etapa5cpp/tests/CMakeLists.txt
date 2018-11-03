cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
file(GLOB object_files
        "../build/*.o"
)
list(FILTER object_files EXCLUDE REGEX ".*main.o.*$")
list(FILTER object_files EXCLUDE REGEX ".*lex.yy.o.*$")
list(FILTER object_files EXCLUDE REGEX ".*parser.tab.o.*$")
file(GLOB test_files
        "unit/*.cpp"
)
add_executable(runTests ${test_files})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread ${object_files})
