cmake_minimum_required(VERSION 3.10)

project(bsc)

set(CMAKE_CXX_STANDARD 17)

add_executable(bsc_sample src/main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)
