cmake_minimum_required(VERSION 3.28)

project(KeyValueStorage
  #  VERSION 0.1 TODO: later
  DESCRIPTION "Key-value storage gRPC"
  LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(contrib)

# add_subdirectory(client) # TODO: later
add_subdirectory(proto)
add_subdirectory(server)

