find_package(grpc CONFIG REQUIRED)
find_package(libprotobuf CONFIG REQUIRED)

set(PROTO_FILES
    v1/keyvalue.proto
    v1/keyvaluestorage.proto
)

add_library(kvstore_proto ${PROTO_FILES})
target_link_libraries(kvstore_proto
    PUBLIC
        grpc::grpc
        grpc::grpc++
        protobuf::libprotobuf
)
target_include_directories(kvstore_proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

get_target_property(grpc_cpp_plugin_location grpc::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET kvstore_proto LANGUAGE cpp)
protobuf_generate(
  TARGET kvstore_proto 
  LANGUAGE grpc 
  GENERATE_EXTENSIONS .grpc.pb.hpp .grpc.pb.cpp 
  PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
)
