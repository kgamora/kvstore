set(SOURCES
    src/main.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(kvstore-server ${SOURCES})
target_link_libraries(kvstore-server
    PRIVATE
        kvstore
)

find_package(GTest REQUIRED)

file(GLOB_RECURSE UT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/lib/*_ut.cpp")

add_executable(kvstore-server-tests ${UT_SOURCES})

target_link_libraries(kvstore-server-tests GTest::gtest GTest::gtest_main)

set_target_properties(kvstore-server-tests PROPERTIES COMPILE_DEFINITIONS "TEST_BUILD")

enable_testing()

include(GoogleTest)
gtest_discover_tests(kvstore-server-tests)
