cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(a-maze-ing)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/third_party/")

# Build libraries
add_subdirectory(src/core)
add_subdirectory(src/graphics)

# Build executable
set(EXE_SOURCES
    src/main.cpp
)

add_executable(a-maze-ing ${EXE_SOURCES})
target_link_libraries(a-maze-ing core graphics)
copy_graphics_runtime(a-maze-ing)
install(TARGETS a-maze-ing)
