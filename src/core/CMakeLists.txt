set(SOURCES
    src/input.cpp
    src/maze.cpp
    src/mazewalk.cpp
    src/mouse.cpp
)

set(HEADERS
    include/input.h
    include/maze.h
    include/mazewalk.h
    include/mouse.h
)

add_library(core ${SOURCES} ${HEADERS})
target_include_directories(core PUBLIC include)
