cmake_minimum_required(VERSION 3.16)
project(AircraftSimulator)

set(CMAKE_CXX_STANDARD 17)

# silence macOS OpenGL warnings, comment out if you're on windows/linux/etc
add_definitions(-DGL_SILENCE_DEPRECATION)

# include directories

include_directories(
    include
    external/imgui
    external/imgui/backends
    external/implot
)

# GLFW

add_subdirectory(external/glfw)

# source files

set(SRC

    src/main.cpp

    src/simulator/Simulator.cpp
    src/simulator/Aircraft.cpp
    src/simulator/Wing.cpp
    src/simulator/Flight_Condition.cpp

    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp

    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp

    external/implot/implot.cpp
    external/implot/implot_items.cpp
)

# create executable

add_executable(simulator ${SRC})

# link libraries

target_link_libraries(simulator
    glfw
    "-framework OpenGL"
)