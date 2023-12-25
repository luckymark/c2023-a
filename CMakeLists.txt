cmake_minimum_required(VERSION 3.26)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_TOOLCHAIN_FILE D:/vcpkg/scripts/buildsystems/vcpkg.cmake)
include_directories(D:/vcpkg/installed/x64-windows/include)
link_directories(D:/vcpkg/installed/x64-windows/lib)
find_package(raylib REQUIRED)
add_executable(untitled1 main.cpp
        play.cpp
        GameTree.cpp
        GameTree.h
        play.h
        test.cpp
        test.h
        draw.cpp
        draw.h)
target_link_libraries(untitled1 raylib)
