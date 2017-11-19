# Minimum CMake Version
cmake_minimum_required(VERSION 3.7)

# Project
project(Snek)

# Modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Packages
find_package(SDL2 REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)

# Release build
set(CMAKE_BUILD_TYPE Release)

# Add src subdirectory
add_subdirectory(src)