cmake_minimum_required(VERSION 3.26)
project(gobangpp)

set(CMAKE_CXX_STANDARD 17)
link_libraries(libeasyx.a)
add_executable(gobangpp main.cpp
        ai.h)

set(CMAKE_EXE_LINKER_FLAGS "-static")