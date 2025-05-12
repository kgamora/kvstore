include(FetchContent)

set(ABSL_PROPAGATE_CXX_STD ON)
set(ABSL_ENABLE_INSTALL ON)

set(FETCHCONTENT_PARALLEL_ENABLE TRUE)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
FetchContent_Declare(
    gRPC
    OVERRIDE_FIND_PACKAGE
    GIT_REPOSITORY https://github.com/grpc/grpc.git
    GIT_TAG v1.70.2
    GIT_PROGRESS   TRUE
    GIT_SHALLOW    TRUE
    USES_TERMINAL_DOWNLOAD TRUE
    GIT_SUBMODULES 
        "third_party/abseil-cpp"
        "third_party/cares/cares"
        "third_party/protobuf"
        "third_party/re2"
        "third_party/boringssl-with-bazel"
        "third_party/zlib"
)

set(protobuf_INSTALL ON)
set(protobuf_BUILD_TESTS OFF)
set(protobuf_BUILD_PROTOC ON)
set(protobuf_MODULE_COMPATIBLE ON)


FetchContent_MakeAvailable(gRPC)


set(Protobuf_SOURCE_DIR "${grpc_SOURCE_DIR}/third_party/protobuf")

# Source: https://stackoverflow.com/a/74844763
include(${Protobuf_SOURCE_DIR}/cmake/protobuf-generate.cmake)

set(gRPC_BUILD_TESTS OFF)
set(gRPC_BUILD_CODEGEN ON)
set(gRPC_BUILD_GRPC_CPP_PLUGIN ON)
set(gRPC_BUILD_CSHARP_EXT OFF)
set(gRPC_BUILD_GRPC_CSHARP_PLUGIN OFF)
set(gRPC_BUILD_GRPC_NODE_PLUGIN OFF)
set(gRPC_BUILD_GRPC_OBJECTIVE_C_PLUGIN OFF)
set(gRPC_BUILD_GRPC_PHP_PLUGIN OFF)
set(gRPC_BUILD_GRPC_PYTHON_PLUGIN OFF)
set(gRPC_BUILD_GRPC_RUBY_PLUGIN OFF)

set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_REFLECTION grpc++_reflection)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
set(_GRPC_GRPCPP grpc++)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
