project(homework)
cmake_minimum_required(VERSION 3.19)

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

# set(CMAKE_C_FLAGS "-Wall -g -fno-discard-value-names")
# set(CMAKE_CXX_FLAGS "-Wall -std=c++20 -g -fno-discard-value-names")

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 添加自定义的Pass
add_subdirectory(Passes)
enable_testing()
add_test(NAME puzzle1_case1 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/bin/puzzle1_case1)
set_tests_properties(puzzle1_case1 PROPERTIES PASS_REGULAR_EXPRESSION "Basic Block Coverage: 5/6")
add_test(NAME puzzle2_stateful COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/bin/puzzle2_stateful)
set_tests_properties(puzzle2_stateful PROPERTIES PASS_REGULAR_EXPRESSION "shared variables: [count, data2]")
add_test(NAME puzzle3_race1 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/bin/puzzle3_race1)
set_tests_properties(puzzle3_race1 PROPERTIES PASS_REGULAR_EXPRESSION "race variables: [data1, data3]")