include(FetchContent)
FetchContent_Declare(
  protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG v28.3
  OVERRIDE_FIND_PACKAGE
)

set(protobuf_BUILD_TESTS OFF)
set(protobuf_BUILD_CONFORMANCE OFF)
set(protobuf_BUILD_EXAMPLES OFF)
set(protobuf_BUILD_PROTOC_BINARIES ON)

FetchContent_GetProperties(protobuf)

FetchContent_Declare(
  grpc
  GIT_REPOSITORY https://github.com/grpc/grpc.git
  GIT_TAG        v1.68.0
  OVERRIDE_FIND_PACKAGE
)
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

set(gRPC_PROTOBUF_PROVIDER "package")

FetchContent_GetProperties(grpc)

FetchContent_MakeAvailable(protobuf grpc)

# Get source directory of the Protobuf
FetchContent_GetProperties(Protobuf SOURCE_DIR Protobuf_SOURCE_DIR)
# Include the script which defines 'protobuf_generate'
include(${Protobuf_SOURCE_DIR}/cmake/protobuf-generate.cmake)

#target_compile_options(
#  grpc
#  -DgRPC_INSTALL=ON
#)
