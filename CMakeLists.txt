cmake_minimum_required(VERSION 3.10)
project(shelly)

set(CMAKE_CXX_STANDARD 17)

# header files
include_directories(include)

# source files

file(GLOB SOURCES "src/*.cpp")
add_executable(shelly ${SOURCES})