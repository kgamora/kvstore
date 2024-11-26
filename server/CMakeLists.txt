set(SOURCES
    src/main.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(kvstore-server ${SOURCES})
target_link_libraries(kvstore-server
    PRIVATE
        kvstore
)

