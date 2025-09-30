cmake_minimum_required(VERSION 4.0)
project(temp_chat)

set(CMAKE_CXX_STANDARD 17)

include_directories(utils)

add_executable(temp_chat
        src/server.cpp
        utils/server.hpp
        main.cpp)
