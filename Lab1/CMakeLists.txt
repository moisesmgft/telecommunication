cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Lab1 VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add library targets
add_library(Hamming hamming.cpp)
add_library(Student mr.cpp)
add_library(Bits bits.cpp)

# Add the executable
add_executable(Lab1 main.cpp)

# Link libraries with the executable
target_link_libraries(Lab1 PUBLIC Hamming MR Bits)
