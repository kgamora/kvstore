include(FetchContent)
FetchContent_Declare(
  protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG v28.3
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

set(gRPC_PROTOBUF_PROVIDER "package" CACHE STRING "" FORCE)

FetchContent_MakeAvailable(grpc protobuf)

#target_compile_options(
#  grpc
#  -DgRPC_INSTALL=ON
#)
