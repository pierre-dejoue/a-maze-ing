
include(sfml)

set(SOURCES
    src/graphics.cpp
)

set(HEADERS
    include/graphics.h
)

add_library(graphics STATIC ${SOURCES} ${HEADERS})

target_include_directories(graphics
    PUBLIC
    include
)

target_link_libraries(graphics
    PUBLIC
    SFML::Graphics
    PRIVATE
    core
)
