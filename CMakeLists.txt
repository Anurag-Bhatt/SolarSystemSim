cmake_minimum_required(VERSION 3.10)
project(SolarSystemSim)

set(CMAKE_CXX_STANDARD 17)

# Output to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Include directories
include_directories(
    include
    include/IMGUI
    include/IMGUI/backend
    third_party/IMGUI
    third_party/IMGUI/backend
)

# Source files
file(GLOB SRC_FILES
    src/*.cpp
)

file(GLOB IMGUI_CORE
    third_party/IMGUI/imgui.cpp
    third_party/IMGUI/imgui_draw.cpp
    third_party/IMGUI/imgui_tables.cpp
    third_party/IMGUI/imgui_widgets.cpp
    third_party/IMGUI/imgui_demo.cpp     # optional
    third_party/IMGUI/imgui_stdlib.cpp
)

file(GLOB IMGUI_BACKEND
    third_party/IMGUI/backend/imgui_impl_sdl3.cpp
    third_party/IMGUI/backend/imgui_impl_sdlrenderer3.cpp
)

add_executable(SolarSystemSim
    ${SRC_FILES}
    ${IMGUI_CORE}
    ${IMGUI_BACKEND}
)

# SDL3 linking
find_package(SDL3 REQUIRED)
target_link_libraries(SolarSystemSim SDL3::SDL3)
