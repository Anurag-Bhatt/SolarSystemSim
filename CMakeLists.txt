cmake_minimum_required(VERSION 3.10)
project(SolarSystemSim)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

add_executable(SolarSystemSim ${SOURCES})

# SDL3 linking (adjust as needed)
find_package(SDL3 REQUIRED)
target_link_libraries(SolarSystemSim SDL3::SDL3)
