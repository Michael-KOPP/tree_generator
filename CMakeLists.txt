cmake_minimum_required(VERSION 3.20)

project(3d)

set(CMAKE_CXX_STANDARD 20)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

set(HEADERS window/window.hpp window/window_factory.h graphics/mesh.h graphics/shader.h  graphics/renderer.h graphics/tree_mesh.h graphics/tree_renderer.h graphics/buffer.hpp core/entity.h core/world.h core/tree.h core/defs.h)

set(SOURCES main.cpp window/window.cpp window/window_factory.cpp graphics/mesh.cpp graphics/shader.cpp graphics/tree_mesh.cpp graphics/tree_renderer.cpp core/entity.cpp core/world.cpp core/tree.cpp)

add_executable(3d ${SOURCES} ${HEADERS}
    core/camera.h core/camera.cpp)

target_link_libraries(3d PRIVATE glfw glad::glad)

target_include_directories(3d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
