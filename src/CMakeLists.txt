
include_directories(BEFORE Physics)

add_executable(Game Main.cpp)
target_link_libraries(Game Physics)

