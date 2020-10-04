cmake_minimum_required(VERSION 3.0)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


project(a-maze-ing)


set(SOURCES
    src/core/src/input.cpp
    src/core/src/maze.cpp
    src/core/src/mazewalk.cpp
    src/core/src/mouse.cpp
    src/graphics/src/graphics.cpp
    src/main.cpp
)


set(HEADERS
    src/core/include/input.h
    src/core/include/maze.h
    src/core/include/mazewalk.h
    src/core/include/mouse.h
    src/graphics/include/graphics.h
)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)


## Look for SFML dependency
# In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIR})


add_executable(a-maze-ing ${SOURCES} ${HEADERS})
target_include_directories(a-maze-ing PRIVATE src/core/include src/graphics/include)
target_link_libraries(a-maze-ing sfml-graphics)
