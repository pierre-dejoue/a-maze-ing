# Build main executable
set(EXE_SOURCES
    src/main.cpp
)

add_executable(a-maze-ing ${EXE_SOURCES})

target_link_libraries(a-maze-ing
    PRIVATE
    core
    graphics
)

install(TARGETS a-maze-ing)
