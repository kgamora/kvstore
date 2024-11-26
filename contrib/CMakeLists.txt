include(FetchContent)
FetchContent_Declare(
  protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG v28.3
)

FetchContent_Declare(
  grpc
  GIT_REPOSITORY https://github.com/grpc/grpc.git
  GIT_TAG        v1.68.0
  CMAKE_ARGS     -Dgrpc_PROTOBUF_PROVIDER=package
)
FetchContent_MakeAvailable(grpc protobuf)

#target_compile_options(
#  grpc
#  -DgRPC_INSTALL=ON
#)
