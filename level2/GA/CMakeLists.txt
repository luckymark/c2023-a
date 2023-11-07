cmake_minimum_required(VERSION 3.26)
project(ga)

set(CMAKE_CXX_STANDARD 17)

add_executable(ga main.cpp
        ga.h
        ga.cpp)
