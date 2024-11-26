find_package(gRPC CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)

set(PROTO_FILES
    kvstore/keyvalue.proto
    kvstore/keyvaluestorage.proto
)

add_library(kvstore ${PROTO_FILES})
target_link_libraries(
  kvstore
  PUBLIC
    gRPC::grpc
    gRPC::grpc++
    protobuf::libprotobuf
)
target_include_directories(kvstore PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET kvstore LANGUAGE cpp)
protobuf_generate(
  TARGET kvstore
  LANGUAGE grpc 
  GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
  PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
)
