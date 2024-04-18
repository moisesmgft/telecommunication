cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(telecommunication VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add library targets
add_library(Hamming src/hamming.cpp)
add_library(MR src/mr.cpp)
add_library(Bits src/bits.cpp)
# add_library(LPDC src/ldpc.cpp)

# Add the executable
add_executable(Lab1 lab1.cpp)
add_executable(Lab2 lab2.cpp)

# Link libraries with the executable
target_link_libraries(Lab1 PUBLIC Hamming MR Bits)
# target_link_libraries(Lab2 PUBLIC Hamming MR Bits LDPC)