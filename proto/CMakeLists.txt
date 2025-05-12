find_package(gRPC CONFIG REQUIRED)

set(PROTO_FILES
    kvstore/keyvalue.proto
    kvstore/keyvaluestorage.proto
)

add_library(kvstore ${PROTO_FILES})
target_link_libraries(
  kvstore
  PUBLIC
    grpc
    grpc++
    libprotobuf
)
target_include_directories(kvstore PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate(TARGET kvstore LANGUAGE cpp)
protobuf_generate(
  TARGET kvstore
  LANGUAGE grpc 
  GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
  PLUGIN "protoc-gen-grpc=$<TARGET_FILE:grpc_cpp_plugin>"
)
