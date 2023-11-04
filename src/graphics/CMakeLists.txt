
include(sfml)

set(SOURCES
    src/graphics.cpp
)

set(HEADERS
    include/graphics.h
)

add_library(graphics STATIC ${SOURCES} ${HEADERS})
target_include_directories(graphics PUBLIC include)
target_link_libraries(graphics PUBLIC sfml-graphics PRIVATE core)

function(copy_graphics_runtime TARGET)
# Adapted from: https://github.com/SFML/cmake-sfml-project
    if(WIN32)
        add_custom_command(
            TARGET ${TARGET}
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${TARGET}>
            VERBATIM)
    endif()
endfunction()
