cmake_minimum_required(VERSION 3.10)
project(HFTSimulation LANGUAGES CXX)

# Specify the C++ standard (you can choose C++17 or C++20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(include)

# Add the executable, using sources from the src directory
file(GLOB SOURCES "src/*.cpp")
add_executable(HFTSimulation ${SOURCES})

# Optionally, you can enable extra warnings
if(MSVC)
    target_compile_options(HFTSimulation PRIVATE /W4)
else()
    target_compile_options(HFTSimulation PRIVATE -Wall -Wextra -pedantic)
endif()

