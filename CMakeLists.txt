cmake_minimum_required(VERSION 3.0)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


project(a-maze-ing)


set(SOURCES
    src/graphics.cpp
    src/input.cpp
    src/main.cpp
    src/maze.cpp
    src/mazewalk.cpp
    src/mouse.cpp
)


set(HEADERS
    src/graphics.h
    src/input.h
    src/maze.h
    src/mazewalk.h
    src/mouse.h
)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)


## Look for SFML dependency
# In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIR})


add_executable(a-maze-ing ${SOURCES} ${HEADERS})
target_include_directories(a-maze-ing PRIVATE src/)
target_link_libraries(a-maze-ing sfml-graphics)
