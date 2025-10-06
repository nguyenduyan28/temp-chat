cmake_minimum_required(VERSION 4.0)
project(temp_chat)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils)

add_executable(server src/server.cpp run_server.cpp)
add_executable(client src/client.cpp run_client.cpp)
