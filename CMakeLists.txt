cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(a-maze-ing)

# Third party dependencies
# SFML
# In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
endif()
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# Build libraries
add_subdirectory(src/core)
add_subdirectory(src/graphics)

# Build executable
set(SOURCES
    src/main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)
add_executable(a-maze-ing ${SOURCES})
target_link_libraries(a-maze-ing core graphics sfml-graphics)
