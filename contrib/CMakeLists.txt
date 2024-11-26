include(FetchContent)

FetchContent_Declare(
    cli11
    QUIET
    OVERRIDE_FIND_PACKAGE
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.4.2
)

FetchContent_MakeAvailable(cli11)

