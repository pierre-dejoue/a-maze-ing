set(SOURCES
    src/graphics.cpp
)

set(HEADERS
    include/graphics.h
)

add_library(graphics ${SOURCES} ${HEADERS})
target_include_directories(graphics PUBLIC include)
target_link_libraries(graphics PRIVATE core sfml-graphics)
