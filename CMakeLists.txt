cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(HOMEBREW_PREFIX "/opt/homebrew"
    CACHE PATH "Path to homebrew installation")

if (APPLE)
    include_directories(
        "${HOMEBREW_PREFIX}/include"
        )

    link_directories(
        "${HOMEBREW_PREFIX}/lib"
        )

    set(CMAKE_CXX_STANDARD 17)
endif()

project(berkecamuk-hatiku VERSION 0.2)

add_subdirectory(src/Physics)
add_subdirectory(src)

add_custom_target(run
    COMMAND src/Game
    DEPENDS Game
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

