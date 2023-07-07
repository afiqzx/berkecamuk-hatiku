cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

project(berkecamuk-hatiku VERSION 0.1)

add_subdirectory(src/Physics)
add_subdirectory(src)

