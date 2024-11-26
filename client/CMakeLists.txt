find_package(cli11 CONFIG REQUIRED)

set(SOURCES
    src/main.cpp
    src/lib/app.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(kvstore-client ${SOURCES})
target_link_libraries(kvstore-client
    PRIVATE
        CLI11::CLI11
        kvstore
)

