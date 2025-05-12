include(FetchContent)

FetchContent_Declare(
    GTest
    QUIET
    OVERRIDE_FIND_PACKAGE
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(GTest)

