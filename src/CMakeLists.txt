include_directories(BEFORE Physics ${SDL2_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)

add_executable(Game Main.cpp Application.cpp Graphics.cpp)
target_link_libraries(Game Physics ${SDL2_LIBRARIES} SDL2_gfx)
